#include "../../includes/error.h"

void	print_err(char *err, bool errno)
{
	if (errno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd(err, STDERR_FILENO);
	}
}

void	print_err(char *err, int status, bool errno)
{
	if (errno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd(err, STDERR_FILENO);
	}
	exit(status);
}
