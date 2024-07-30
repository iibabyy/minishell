#include "parsing_utils.h"

/*
This function transform tokens to a binary tree
while checking if there is any errors
*/
t_command	*token_to_ast(t_token *token)
{
	t_command	*command;
	t_command	*current;
	
	while (token != NULL)
	{
		command = init_command();
		if (command == NULL)
			return (NULL);
		if (add_words_to_command(command, &token) == EXIT_FAILURE)
			return (free_2d_array((void ***)&command->command), ft_free(command), NULL);
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

int	add_words_to_command(t_command *command, t_token **token)
{
	t_command	*command;
	int			i;

	if ((*token)->type != WORD)
		return (parse_err(TOKEN_ERR, (*token)->content), EXIT_FAILURE);
	i = 0;
	while ((*token)->type == WORD)
	{
		command->command[i++] = (*token)->content;
		(*token) = (*token)->next;
		while ((*token)->type == REDIRECTION)
		{
			if (add_redirections_to_command(command, token) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			(*token) = (*token)->next;
		}
	}
	command->command[i] = NULL;
	return (EXIT_SUCCESS);
}
