/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:08:56 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:19:55 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	token_to_operator_type(t_token *token)
{
	char	*content;

	content = token->content;
	if (token == NULL)
		return (-1);
	else if (ft_strcmp(content, "||") == 0)
		return (OR);
	else if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(content, "&&") == 0)
		return (AND);
	else
		return (-1);
}

int	args_number(t_token *token)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (0);
	token = token->next;
	while (token != NULL && token->type != OPERATOR)
	{
		if (token->type == REDIRECTION)
		{
			if (token->next == NULL || token->next->next == NULL)
				return (i);
			token = token->next->next;
		}
		++i;
		token = token->next;
	}
	return (i);
}

t_command	*init_command(t_parsing *data)
{
	t_command	*command;

	(void)data;
	command = ft_calloc(1, sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->infile = STDIN_FILENO;
	command->outfile = STDOUT_FILENO;
	command->previous = NULL;
	command->type = COMMAND;
	command->command = ft_malloc
		(sizeof(char *) * (args_number(data->curr_token) + 2));
	if (command->command == NULL)
		return (NULL);
	command->command[0] = NULL;
	command->is_child = false;
	return (command);
}

t_command	*last_command(t_command *current)
{
	if (current == NULL)
		return (NULL);
	while (current->previous != NULL)
		current = current->previous;
	return (current);
}

int	add_words_to_command(t_parsing *data)
{
	t_command	*command;
	int			i;

	free((command = data->command, i = 0, NULL));
	if (command == NULL || data->curr_token == NULL)
		return (EXIT_FAILURE);
	while (data->curr_token != NULL && data->curr_token->type != OPERATOR)
	{
		if (data->curr_token->type == WORD)
			command->command[i++] = data->curr_token->content;
		else if (data->curr_token->type == PARENTHESIS)
		{
			if (i != 0)
				return (parse_err(TOKEN_ERR, "("), EXIT_FAILURE);
			command->command[i++] = data->curr_token->content;
			command->type = SUB_SHELL;
		}
		else if (data->curr_token->type == REDIRECTION)
		{
			if (add_redirection(data) == EXIT_FAILURE)
				return (command->command[i] = NULL, EXIT_FAILURE);
		}
		data->curr_token = data->curr_token->next;
	}
	return (command->command[i] = NULL, EXIT_SUCCESS);
}
