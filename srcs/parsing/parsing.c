#include "parsing_utils.h"

/*
This function transform tokens to a binary tree
while checking if there is any errors
*/
t_command	*token_to_ast(t_token *token)
{
	t_parsing	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	data.token = token;
	data.curr_token = token;
	while (data.curr_token != NULL)
	{
		data.curr_command = init_command();
		if (command == NULL)
			return (NULL);
		if (data.command == NULL)
			data.command = data.curr_command;
		if (add_words_to_command(&data) == EXIT_FAILURE)
			return (NULL);
	}
}

t_command	*init_command(void)
{
	t_command	*command;

	command = ft_malloc(sizeof(t_command) * 1);
	if (command == NULL)
		return (NULL);
	command->infile = STDIN_FILENO;
	command->outfile = STDOUT_FILENO;
	command->type = COMMAND;
}

int	add_words_to_command(t_parsing *data)
{
	t_token		*token;
	t_command	*command;
	int		i;

	command = data->curr_command;
	token = data->curr_token;
	if (token->type != WORD)
		return (parse_err(TOKEN_ERR, token->content), EXIT_FAILURE);
	i = 0;
	while (token->type == WORD)
	{
		command[i++] = token->content;
		token = token->next;
		while (token->type == REDIRECTION)
		{
			if (add_redirections_to_command(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			token = token->next;
		}
	}
	command[i] = NULL;
	data->curr_token = token;
	return (EXIT_SUCCESS);
}
