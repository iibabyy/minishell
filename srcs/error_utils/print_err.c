#include "errors_utils.h"

void	print_err(char *err, bool errno)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd(err, STDERR_FILENO);
	}
}

void	parse_err(char *error, char *token, t_parsing *data)
{
	destroy_tokens(data->token);
	destroy_commands(data->command);
	destroy_here_docs(data->here_doc);
	if (token == NULL)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("Error: syntaxe error near token '", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
}

void	print_err_and_exit(char *err, int status, bool errno)
{
	print_err(err, errno);
	exit(status);
}
