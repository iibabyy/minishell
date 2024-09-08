#include "built_in.h"

int	exit(char **arg)
{
	bool	one_arg;
	bool	first_arg_ok;

	if (arg[1] == NULL)
		free_and_exit(get_code(0, false));
	one_arg = is_one_arg(arg);
	first_arg_ok = is_first_arg_ok(arg);
}

bool	is_first_arg_ok(char **arg)
{
	int	i;
	if (arg == NULL || arg[1] == NULL)
		return (false);
	i = -1;
	while (arg[1][++i] != '\0')
	{
		if (ft_isdigit(arg[1][i]) == false)
			return (false);
	}
}

bool	is_one_arg(char **arg)
{
	if (arg == NULL || arg[1] == NULL)
		return (false);
	if (arg[1] != NULL && arg[2] == NULL)
		return (true);
	ft_putstr_fd("", STDERR_FILENO);
	return (false);
}
