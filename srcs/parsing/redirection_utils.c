#include "parsing.h"

t_redirection	*init_redirection(t_parsing *data, int type, int o_flags)
{
	t_redirection	*redirection;

	redirection = ft_malloc(sizeof(t_redirection) * 1);
	if (redirection == NULL)
		return (print_err("init_redirection(): ft_malloc() function failed",
				true), NULL);
	ft_memset(redirection, 0, sizeof(t_redirection));
	if (type == REDIRECTION)
		redirection->here_doc = init_here_doc(data);
	else
	{
		redirection->type = type;
		redirection->o_flags = o_flags;
		redirection->command = data->command;
		redirection->token = data->curr_token;
		data->curr_token = data->curr_token->next;
		redirection->file = data->curr_token;
	}
	return (redirection);
}

int	type_to_oflags(int type)
{
	if (type == OUTPUT)
		return (O_WRONLY);
	if (type == APPEND_OUTPUT)
		return (O_WRONLY | O_APPEND);
	if (type == INPUT)
		return (O_RDONLY);
	if (type == HERE_DOC)
		return (O_RDWR | O_APPEND);
	return (-1);
}

t_redirection	*last_redirection(t_redirection *redirection)
{
	while (redirection->next != NULL)
		redirection = redirection->next;
	return (redirection);
}

int	check_redirection(t_redirection	*redirection)
{
	t_token	*token;
	char	*type;

	token = redirection->token;
	if (redirection->type == INPUT)
		type = "<";
	if (redirection->type == HERE_DOC)
		type = "<<";
	if (redirection->type == OUTPUT)
		type = ">";
	if (redirection->type == APPEND_OUTPUT)
		type = ">>";
	if (ft_strcmp(token->content, type) != 0)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	if (token->type != WORD || token->type != STRING)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}