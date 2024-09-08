#include "built_in.h"

int	exit(char **arg)
{
	int	i;

	if (arg == NULL)
		free_and_exit(get_code(0, false));
	if (exit_parse(arg[0]) == EXIT_FAILURE)
}
