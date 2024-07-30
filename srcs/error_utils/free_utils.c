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
	t_here_doc	*temp;

	while (here_doc != NULL)
	{
		temp = here_doc;
		here_doc = here_doc->next;
		ft_close_fd(&temp->pipe[0]);
		ft_close_fd(&temp->pipe[1]);
		ft_free(temp);
	}
}
