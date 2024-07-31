#include "parsing.h"

int	add_redirection(t_parsing *data)
{
	char	*token;

	token = data->curr_token->content;
	if (data->curr_token->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (add_redirection_to_data(data, OUTPUT));
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (add_redirection_to_data(data, APPEND_OUTPUT));
	else if (ft_strncmp(token, "<", 1) == 0)
		return (add_redirection_to_data(data, INPUT));
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (add_redirection_to_data(data, HERE_DOC));
	else
		return (EXIT_FAILURE);
}

int	add_redirection_to_data(t_parsing *data, int type)
{
	t_redirection	*redirection;

	redirection = init_redirection(data, type, type_to_oflags(type));
	if (redirection == NULL)
		return (EXIT_FAILURE);
	if (data->redirection == NULL)
		data->redirection = redirection;
	else
		last_redirection(data->redirection)->next = redirection;
	data->curr_token = data->curr_token->next;
	return (EXIT_SUCCESS);
}

int	open_redirections(t_redirection	*redirection)
{
	redirection = parse_redirections(redirection);
	if (redirection == NULL)
		return (EXIT_FAILURE);
	while (redirection != NULL)
	{
		if (redirection->type == HERE_DOC)
		{
			if (open_here_doc(redirection) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			if (open_file(redirection) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}

t_redirection	*parse_redirections(t_redirection *redirection)
{
	t_redirection	*temp;
	t_redirection	*before_temp;

	temp = redirection;
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
		return (NULL);
	else
		before_temp->next = NULL;
	return (redirection);
}

int	open_file(t_redirection *redirection)
{
	int	*target_command_fd;
	int	type;
	int	fd;

	fd = open(redirection->file->content, redirection->o_flags);
	if (fd == -1)
		return (EXIT_FAILURE);
	type = redirection->type;
	if (type == OUTPUT || type == APPEND_OUTPUT)
		target_command_fd = &redirection->command->outfile;
	else
		target_command_fd = &redirection->command->infile;
	*target_command_fd = fd;
	return (EXIT_SUCCESS);
}
