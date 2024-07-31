#include "parsing.h"

/*
Take an string as parameter.
Return the first operator of an AST.
Return NULL if an error occurs
*/
t_command	*parse(char	*input)
{
	t_parsing	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	data.token = input_to_tokens(input);
	if (token == NULL)
		return (destroy_parsing(&data), NULL);
	data.command = token_to_ast(token);
	if (command == NULL)
		return (destroy_parsing(&data), NULL);
	if (open_redirections(data.redirection) == EXIT_FAILURE)
		return (destroy_parsing(&data), NULL);
	destroy_tokens(data.token);
	destroy_redirections(data.redirection);
	return (data.command)
}


/*
This function transform tokens to a binary tree
while checking if there is any errors
*/
t_command	*token_to_ast(t_parsing *data)
{
	t_command	*command;

	command = init_command(data);
	if (command == NULL)
		return (NULL);
	if (add_words_to_command(data) == EXIT_FAILURE)
		return (NULL);
	if (data->curr_token == NULL)
		return (command);
	command->previous = init_operator(data, command);
	command->previous->right = token_to_ast(data->curr_token);
	return (command->previous);
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
	command->type = COMMAND;
	command->command = ft_malloc(sizeof(char *) * 5);
	return (command);
}

int	add_words_to_command(t_parsing *data)
{
	t_token		*token;
	t_command	*command;
	int		i;

	command = data->command;
	token = data->curr_token;
	if (token == NULL || command == NULL)
		return (EXIT_FAILURE);
	if (token->type != WORD && token->type != STRING)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	i = 0;
	while (token != NULL && (token->type == WORD || token->type == STRING))
	{
		command->command[i++] = token->content;
		token = token->next;
		while (token != NULL && token->type == REDIRECTION)
		{
			if (add_redirection(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			token = token->next;
		}
	}
	command->command[i] = NULL;
	data->curr_token = token;
	return (EXIT_SUCCESS);
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
		return (print_err("init_operator(): ft_calloc() failed", false), NULL);
	operator->type = token_to_operator_type(current);
	if (operator->type == -1)
		return (parse_err(TOKEN_ERR, current->content), NULL);
	operator->left = left_command;
	operator->right = NULL;
	data->curr_token = data->curr_token->next;
	return (operator);
}
