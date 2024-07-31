#include "parsing.h"

int	add_redirection(t_parsing *data)
{
	char	*token;

	token = data->curr_token->content;
	if (data->curr_token->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (add_redirection_to_data(data, OUTPUT));
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (add_redirection_to_data(data, APPEND_OUTPUT));
	else if (ft_strncmp(token, "<", 1) == 0)
		return (add_redirection_to_data(data, INPUT));
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (add_redirection_to_data(data, HERE_DOC));
	else
		return (EXIT_FAILURE);
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
		last_redirection(data->redirection)->next = redirection;
	data->curr_token = data->curr_token->next;
	return (EXIT_SUCCESS);
}
