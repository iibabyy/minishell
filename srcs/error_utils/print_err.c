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

void	print_err_and_exit(char *err, int status, bool errno)
{
	print_err(err, errno);
	exit(status);
}
