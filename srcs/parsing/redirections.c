#include "parsing_utils.h"

int	add_redirection(t_parsing *data)
{
	char	*token;

	token = data->curr_token->content;
	if (data->curr_token->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strcmp(token, ">") == 0)
		return (add_redirection(data, OUTPUT));
	else if (ft_strcmp(token, ">>") == 0)
		return (add_redirection(data, APPEND_OUTPUT));
	else if (ft_strcmp(token, "<") == 0)
		return (add_redirection(data, INPUT));
	else if (ft_strcmp(token, "<<") == 0)
		return (add_here_doc(data));
	else
		return (parse_err(TOKEN_ERR, token), EXIT_FAILURE);
}

int	add_redirection_to_data(t_parsing *data, int type)
{
	t_redirection	*redirection;

	redirection = init_redirection(data, type, type_to_oflags(type));
	if (redirection == NULL)
		return (EXIT_FAILURE);
	if (data->redirection == NULL)
		data->redirection = redirection;
	else
		find_last_redirection(data->redirection)->next = redirection;
}
