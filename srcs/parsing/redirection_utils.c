/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:08:00 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 11:49:20 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redirection	*init_redirection(t_parsing *data, int type, int o_flags)
{
	t_redirection	*redirection;

	if (type == HERE_DOC)
	{
		redirection = init_here_doc(data);
		if (redirection == NULL)
			return (NULL);
		if (open_here_doc(redirection) == EXIT_FAILURE)
			return (NULL);
	}
	else
	{
		redirection = init_others_redirection(data, type, o_flags);
	}
	return (redirection);
}

t_redirection	*init_others_redirection(t_parsing *data, int type, int o_flags)
{
	t_redirection	*redirection;

	redirection = ft_calloc(1, sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->type = type;
	redirection->o_flags = o_flags;
	redirection->command = data->command;
	redirection->token = data->curr_token;
	data->curr_token = data->curr_token->next;
	if (data->curr_token == NULL)
		return (parse_err(TOKEN_ERR, "newline"), ft_free(redirection), NULL);
	if (data->curr_token->type != WORD)
		return (parse_err(TOKEN_ERR, data->curr_token->content),
			ft_free(redirection), NULL);
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

bool	is_standart_fd(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (true);
	return (false);
}
