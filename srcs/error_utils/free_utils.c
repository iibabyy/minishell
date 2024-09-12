/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:47 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/12 20:32:18 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"
/*
take the first AST command and destroy all the AST commands
it don't free() the command 2d char array: the destroy_tokens() function does it
*/
void	destroy_commands(t_command *command)
{
	if (command == NULL)
		return ;
	if (command->left != NULL)
		destroy_commands(command->left);
	if (command->right != NULL)
		destroy_commands(command->right);
	if (command->infile != STDIN_FILENO)
		ft_close_fd(&command->infile);
	if (command->outfile != STDOUT_FILENO)
		ft_close_fd(&command->outfile);
	ft_free(command);
}

void	destroy_tokens(t_token *token)
{
	t_token	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		ft_free(temp->content);
		ft_free(temp);
	}
}

void	destroy_here_docs(t_here_doc *here_doc)
{
	ft_close_fd(&here_doc->pipe[0]);
	ft_close_fd(&here_doc->pipe[1]);
	ft_free(here_doc);
}

void	destroy_redirections(t_redirection *redirection)
{
	t_redirection	*temp;

	while (redirection != NULL)
	{
		temp = redirection;
		redirection = redirection->next;
		if (temp->type == HERE_DOC)
			destroy_here_docs(temp->here_doc);
		ft_free(temp);
	}
}

void	destroy_parsing(t_parsing *data)
{
	if (data->error == true)
		return ;
	if (data->token != NULL)
		destroy_tokens(data->token);
	if (data->command != NULL)
		destroy_commands(data->command);
	data->error = true;
}
