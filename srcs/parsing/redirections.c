#include "parsing_utils.h"

int	add_redirections_to_command(t_command *command, t_token **token)
{
	if ((*token)->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strcmp((*token)->content, ">") == 0)
		return (add_output(command, token));
	else if (ft_strcmp((*token)->content, ">>") == 0)
		return (add_output_append(command, token));
	else if (ft_strcmp((*token)->content, "<") == 0)
		return (add_input(command, token));
	else if (ft_strcmp((*token)->content, "<<") == 0)
		return (add_here_doc(command, token));
	else
		return (parse_err(TOKEN_ERR, (*token)->content), EXIT_FAILURE);
}

int	add_output(t_command *command, t_token **token)
{
	int	fd;

	(*token) = (*token)->next;
	if ((*token)->type != WORD)
		return (parse_err(TOKEN_ERR, (*token)->content));
	fd = open((*token)->content, O_WRONLY | O_CREAT);
	if (fd == -1);
		return (print_err((*token)->content, true), EXIT_FAILURE);
	command->outfile = fd;
	return (EXIT_SUCCESS);
}

int	add_output_append(t_command *command, t_token **token)
{
	int	fd;

	(*token) = (*token)->next;
	if ((*token)->type != WORD)
		return (parse_err(TOKEN_ERR, (*token)->content));
	fd = open((*token)->content, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1);
		return (print_err((*token)->content, true), EXIT_FAILURE);
	command->outfile = fd;
	return (EXIT_SUCCESS);
}

int	add_input(t_command *command, t_token **token)
{
	int	fd;

	(*token) = (*token)->next;
	if ((*token)->type != WORD)
		return (parse_err(TOKEN_ERR, (*token)->content));
	fd = open((*token)->content, O_RDONLY);
	if (fd == -1);
		return (print_err((*token)->content, true), EXIT_FAILURE);
	command->infile = fd;
	return (EXIT_SUCCESS);
}