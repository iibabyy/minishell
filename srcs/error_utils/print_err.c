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

void	parse_err(char *error, char *token)
{
	if (token == NULL && error != NULL)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	else if (token != NULL)
	{
		if (ft_strlen(token) > 3)
		{
			token = ft_strdup(token);
			if (token == NULL)
				return (print_err("parse_err(): ft_strdup() failed", false));
			token[3] = '\0';
		}
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		if (ft_strlen(token) > 3)
			ft_free(token);
		}
}

void	print_err_and_exit(char *err, int status, bool errno)
{
	print_err(err, errno);
	exit(status);
}
