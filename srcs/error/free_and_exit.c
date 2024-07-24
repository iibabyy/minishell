#include "../../includes/error.h"

void	free_and_exit(char *err, int status, struct s_data *data, bool errno)
{
	free_all(data);
	if (err != NULL || errno == true)
		print_err(err, errno);
	exit(status);
}

void	free_all(struct s_data *data)
{
	free_garbage(NULL);
}

