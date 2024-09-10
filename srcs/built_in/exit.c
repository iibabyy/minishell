#include "built_in.h"

static bool	first_error(bool getter);
static bool	is_one_arg(char **arg);
static bool	is_first_arg_ok(char **arg);

int	ft_exit(char **arg)
{
	bool	one_arg;
	bool	first_arg_ok;

	first_error(false);
	if (arg == NULL || arg[1] == NULL)
		free_and_exit(get_status());
	first_arg_ok = is_first_arg_ok(arg);
	one_arg = is_one_arg(arg);
	if (first_arg_ok == false)
		free_and_exit(2);
	if (first_arg_ok == true && one_arg == true)
		free_and_exit(ft_atoi(arg[1]));
	return (EXIT_FAILURE);
}

static bool	is_first_arg_ok(char **arg)
{
	int	i;
	if (arg == NULL || arg[1] == NULL)
		return (false);
	i = -1;
	while (arg[1][++i] != '\0')
	{
		if (ft_isdigit(arg[1][i]) == false)
		{
			if (first_error(true) == true)
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(arg[1], STDERR_FILENO);
				ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			}
			return (false);
		}
	}
	return (true);
}

static bool	is_one_arg(char **arg)
{
	if (arg == NULL || arg[1] == NULL)
		return (false);
	if (arg[1] != NULL && arg[2] == NULL)
		return (true);
	if (first_error(true) == true)
		print_err("exit: too many arguments", false);
	return (false);
}

static bool	first_error(bool getter)
{
	static bool	first = true;
	
	if (getter == false)
		return (first = true, true);
	if (first == true)
		return (first = false, true);
	return (false);
}
