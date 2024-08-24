/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:10:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/20 22:30:17 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Take an string as parameter.
Return the first operator of an AST.
Return NULL if an error occurs
*/
t_command	*parse(char	*input)
{
	t_parsing	data;

	if (input == NULL)
		return (NULL);
	ft_memset(&data, 0, sizeof(t_data));
	data.error = false;
	// input = replace_env_vars(input);
	data.token = input_to_tokens(input);
	if (data.token == NULL)
		return (destroy_parsing(&data), NULL);
	add_history(input);
	data.curr_token = data.token;
	data.command = token_to_ast(&data);
	if (data.command == NULL)
		return (destroy_parsing(&data), NULL);
	if (replace_aliases(last_command(data.command)) == EXIT_FAILURE)
		return (destroy_parsing(&data), NULL);
	if (data.command->previous != NULL)
		return (data.command->previous);
	return (data.command);
}

t_command	*token_to_ast(t_parsing *data)
{
	t_command	*first_command;

	first_command = create_command(data);
	data->command = first_command;
	if (first_command == NULL)
		return (destroy_parsing(data), NULL);
	data->command = create_ast(data, first_command);
	if (data->error == true)
		return (NULL);
	return (first_command);
}

t_command	*create_ast(t_parsing *data, t_command *left)
{
	t_command	*operator;

	if (data->curr_token == NULL)
		return (NULL);
	operator = init_operator(data, left);
	if (operator == NULL)
		return (destroy_parsing(data), NULL);
	if (operator->weight < next_operator_weight(data))
	{
		operator->right = last_command(token_to_ast(data));
		if (operator->right == NULL)
			return (destroy_parsing(data), NULL);
	}
	else
	{
		operator->right = create_command(data);
		if (operator->right == NULL)
			return (destroy_parsing(data), NULL);
	}
	left->previous = operator;
	operator->right->previous = operator;
	operator->previous = create_ast(data, operator);
	return (operator);
}

t_command	*create_command(t_parsing *data)
{
	t_command	*command;

	command = init_command(data);
	if (command == NULL)
		return (NULL);
	data->command = command;
	if (add_words_to_command(data) == EXIT_FAILURE)
		return (NULL);
	if (command->command[0] == NULL && command->redirections == NULL)
		return (parse_err(TOKEN_ERR, data->curr_token->content), NULL);
	if (command->type == SUB_SHELL && command->command[1] != NULL)
		return (parse_err(TOKEN_ERR, command->command[1]), NULL);
	return (command);
}

t_command	*init_operator(t_parsing *data, t_command *left_command)
{
	t_command	*operator;
	t_token		*current;

	current = data->curr_token;
	if (current->type != OPERATOR)
		return (parse_err(TOKEN_ERR, current->content), NULL);
	operator = ft_calloc(1, sizeof(t_command));
	if (operator == NULL)
		return (NULL);
	operator->type = token_to_operator_type(current);
	if (operator->type == -1)
		return (parse_err(TOKEN_ERR, current->content), NULL);
	operator->weight = weight_by_type(operator->type);
	if (operator->weight == -1)
		return (parse_err(TOKEN_ERR, current->content), NULL);
	operator->left = left_command;
	operator->right = NULL;
	if (data->curr_token->next == NULL)
		return (parse_err(TOKEN_ERR, data->curr_token->content), NULL);
	if (data->curr_token->next->type != WORD
		&& data->curr_token->next->type != SUB_SHELL)
		return (parse_err(TOKEN_ERR, data->curr_token->content), NULL);
	data->curr_token = data->curr_token->next;
	return (operator);
}
