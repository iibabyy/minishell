#include "parsing.h"

t_redirection	*init_redirection(t_parsing *data, int type, int o_flags)
{
	t_redirection	*redirection;

	if (type == HERE_DOC)
	{
		redirection = init_here_doc(data);
	}
	else
	{
		redirection = init_others_redirection(data, type, o_flags);
	}
	if (data->curr_token == NULL) // || data->curr_token->type != WORD
		return (parse_err(TOKEN_ERR, redirection->token->content), NULL);
	return (redirection);
}

int	check_redirection(t_redirection	*redirection)
{
	t_token	*token;
	char	*type;

	type = NULL;
	if (redirection->type == HERE_DOC)
	{
		if (ft_strcmp(redirection->here_doc->token->content, "<<") != 0)
			return (parse_err(TOKEN_ERR, redirection->here_doc->token->content),
				EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (redirection->type == INPUT)
		type = "<";
	else if (redirection->type == OUTPUT)
		type = ">";
	else if (redirection->type == APPEND_OUTPUT)
		type = ">>";
	token = redirection->token;
	if (ft_strcmp(token->content, type) != 0)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	if (token->type != REDIRECTION)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_redirection	*init_others_redirection(t_parsing *data, int type, int o_flags)
{
	t_redirection	*redirection;

	redirection = ft_calloc(1, sizeof(t_redirection));
	if (redirection == NULL)
		return (print_err("init_here_doc(): ft_calloc() function failed",
				false), NULL);
	redirection->type = type;
	redirection->o_flags = o_flags;
	redirection->command = data->command;
	redirection->token = data->curr_token;
	data->curr_token = data->curr_token->next;
	redirection->file = data->curr_token;
	return (redirection);
}

void	redirect_add_back(t_redirection **lst, t_redirection *redirection)
{
	t_redirection	*last;

	if (redirection == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = redirection;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = redirection;
}

int	ft_open_redirect(t_redirection *redirection)
{
	while (redirection != NULL)
	{
		if (redirection->type == HERE_DOC)
		{
			if (open_here_doc(redirection) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			if (open_file(redirection) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}
