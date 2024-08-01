#include "parsing.h"

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
	if (redirection->type == OUTPUT || redirection->type == APPEND_OUTPUT)
		redirect_add_back(&data->command->outfile, redirection);
	else
		redirect_add_back(&data->command->infile, redirection);
	data->curr_token = data->curr_token->next;
	return (EXIT_SUCCESS);
}

/*
open the redirections linked to the command in parameter
Return 1 if an error occurs, and 0 otherwise
*/
int	open_redirections(t_command	*command)
{
	if	(parse_redirection(command->infile) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_open_redirect(command->infile) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if	(parse_redirection(command->outfile) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_open_redirect(command->outfile) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_redirection(t_redirection *redirection)
{
	t_redirection	*temp;
	t_redirection	*before_temp;

	temp = redirection;
	if (temp == NULL)
		return (EXIT_SUCCESS);
	before_temp = NULL;
	while (temp != NULL)
	{
		if (check_redirection(temp) == EXIT_FAILURE)
		{
			destroy_redirections(temp);
			break ;
		}
		before_temp = temp;
		temp = temp->next;
	}
	if (before_temp == NULL)
		return (EXIT_FAILURE);
	else
		before_temp->next = NULL;
	return (EXIT_SUCCESS);
}

int	open_file(t_redirection *redirection)
{
	int	*target_command_fd;
	int	type;
	int	fd;

	fd = open(redirection->file->content, redirection->o_flags, 0644);
	if (fd == -1)
		return (perror(redirection->file->content), EXIT_FAILURE);
	type = redirection->type;
	if (type == OUTPUT || type == APPEND_OUTPUT)
		target_command_fd = &redirection->command->outfile_fd;
	else
		target_command_fd = &redirection->command->infile_fd;
	*target_command_fd = fd;
	return (EXIT_SUCCESS);
}
