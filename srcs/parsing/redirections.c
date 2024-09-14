/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:08:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:10:43 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"
#include "parsing.h"

void	dup2_here_doc(t_redirection *redirect);

int	add_redirection(t_parsing *data)
{
	char	*token;

	token = data->curr_token->content;
	if (data->curr_token->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (add_redirection_to_command(data, APPEND_OUTPUT));
	else if (ft_strncmp(token, ">", 1) == 0)
		return (add_redirection_to_command(data, OUTPUT));
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (add_redirection_to_command(data, HERE_DOC));
	else if (ft_strncmp(token, "<", 1) == 0)
		return (add_redirection_to_command(data, INPUT));
	else
		return (EXIT_FAILURE);
}

int	add_redirection_to_command(t_parsing *data, int type)
{
	t_redirection	*redirection;

	redirection = init_redirection(data, type, type_to_oflags(type));
	if (redirection == NULL)
		return (EXIT_FAILURE);
	redirect_add_back(&data->command->redirections, redirection);
	return (EXIT_SUCCESS);
}

/*
open the redirections linked to the command in parameter
Return 1 if an error occurs, and 0 otherwise
*/
int	open_redirections(t_command *command)
{
	t_redirection	*redirection;

	redirection = command->redirections;
	while (redirection != NULL)
	{
		if (check_redirection(redirection) == EXIT_FAILURE)
			return (destroy_redirections(command->redirections), EXIT_FAILURE);
		if (redirection->type != HERE_DOC)
		{
			if (open_file(redirection) == EXIT_FAILURE)
				return (destroy_redirections(command->redirections),
					EXIT_FAILURE);
		}
		else
		{
			dup2_here_doc(redirection);
		}
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redirection(t_redirection *redirection)
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

int	open_file(t_redirection *redirection)
{
	int	*target_cmd_fd;
	int	type;
	int	fd;

	fd = open(redirection->file->content, redirection->o_flags, 0644);
	if (fd == -1)
		return (print_err(redirection->file->content, true), EXIT_FAILURE);
	type = redirection->type;
	if (type == INPUT)
	{
		target_cmd_fd = &redirection->command->infile;
		ft_dup2(&fd, STDIN_FILENO);
	}
	else
	{
		ft_dup2(&fd, STDOUT_FILENO);
		target_cmd_fd = &redirection->command->outfile;
	}
	if (is_standart_fd(*target_cmd_fd) == false)
		ft_close_fd(target_cmd_fd);
	*target_cmd_fd = fd;
	return (EXIT_SUCCESS);
}
