#include "parsing_utils.h"

int	add_redirections_to_command(t_parsing *data)
{
	char	*token;

	token = data->curr_token->content;
	if (data->curr_token->type != REDIRECTION)
		return (EXIT_FAILURE);
	else if (ft_strcmp(token, ">") == 0)
		return (add_output(data));
	else if (ft_strcmp(token, ">>") == 0)
		return (add_output_append(data));
	else if (ft_strcmp(token, "<") == 0)
		return (add_input(data));
	else if (ft_strcmp(token, "<<") == 0)
		return (add_here_doc(data));
	else
		return (parse_err(TOKEN_ERR, token), EXIT_FAILURE);
}

int	add_output(t_parsing *data)
{
	int	fd;
	t_token	*token;

	token = data->curr_token
	token = token->next;
	if (token->type != WORD)
		return (parse_err(TOKEN_ERR, data));
	fd = open(token->content, O_WRONLY | O_CREAT);
	if (fd == -1);
		return (print_err(token->content, true), EXIT_FAILURE);
	data->curr_command->outfile = fd;
	return (EXIT_SUCCESS);
}

int	add_output_append(t_parsing *data)
{
	int	fd;
	t_token	*token;

	token = data->curr_token
	token = token->next;
	if (token->type != WORD)
		return (parse_err(TOKEN_ERR, data));
	fd = open(token->content, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1);
		return (print_err(token->content, true), EXIT_FAILURE);
	data->curr_command->outfile = fd;
	return (EXIT_SUCCESS);
}

int	add_input(t_parsing *data)
{
	int	fd;
	t_token	*token;

	token = data->curr_token
	token = token->next;
	if (token->type != WORD)
		return (parse_err(TOKEN_ERR, data));
	fd = open(token->content, O_RDONLY);
	if (fd == -1);
		return (print_err(token->content, true), EXIT_FAILURE);
	data->curr_command->infile = fd;
	return (EXIT_SUCCESS);
}