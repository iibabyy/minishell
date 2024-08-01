#include "parsing.h"

int	token_to_operator_type(t_token *token)
{
	char	*content;

	content = token->content;
	if (token == NULL)
		return (-1);
	else if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(content, "||") == 0)
		return (OR);
	else if (ft_strcmp(content, "&&") == 0)
		return (AND);
	else
		return (-1);
}

int	args_number(t_token *token)
{
	int	i;

	i = 0;
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

t_command	*create_command(t_parsing *data)
{
	t_command	*command;

	command = init_command(data);
	if (command == NULL)
		return (NULL);
	data->command = command;
	if (add_words_to_command(data) == EXIT_FAILURE)
		return (NULL);
	return (command);
}
int	add_words_to_command(t_parsing *data)
{
	t_command	*command;
	int			i;

	// if (data->curr_token->type != WORD && data->curr_token->type != STRING)
	// {
	// 	if (data->curr_token->next == NULL)
	// 		data->curr_token->content = "newline";
	// 	return (parse_err(TOKEN_ERR, data->curr_token->content), EXIT_FAILURE);
	// }
	command = data->command;
	if (command == NULL || data->curr_token == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (data->curr_token != NULL && data->curr_token->type != OPERATOR)
	{
		while (data->curr_token != NULL && (data->curr_token->type == WORD
				|| data->curr_token->type == STRING))
		{
			command->command[i++] = data->curr_token->content;
			data->curr_token = data->curr_token->next;
		}
		while (data->curr_token != NULL && data->curr_token->type == REDIRECTION)
		{
			if (add_redirection(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	command->command[i] = NULL;
	return (EXIT_SUCCESS);
}

t_command	*last_command(t_command *current)
{
	if (current == NULL)
		return (NULL);
	while (current->previous != NULL)
		current = current->previous;
	return (current);
}
