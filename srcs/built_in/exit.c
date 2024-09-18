/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:19:25 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/18 16:53:24 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static		bool	first_error(bool getter);
static		bool	is_one_arg(char **arg);
static		bool	is_first_arg_ok(char **arg);
long long	ft_atol_exit(const char *str);

int	ft_exit(char **arg)
{
	bool	one_arg;
	bool	first_arg_ok;
	int		exit_code;

	first_error(false);
	if (arg == NULL || arg[1] == NULL)
		free_and_exit(get_status());
	first_arg_ok = is_first_arg_ok(arg);
	exit_code = ft_atol_exit(arg[1]);
	one_arg = is_one_arg(arg);
	if (first_arg_ok == false)
		free_and_exit(2);
	if (first_arg_ok == true && one_arg == true)
		free_and_exit((unsigned char)exit_code);
	return (EXIT_FAILURE);
}

long long	ft_atol_exit(const char *str)
{
	long		i;
	long		sign;
	long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -sign;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i++] - '0');
		if (number > LONG_MAX)
		{
			print_err("exit: numeric argument required", false);
			free_and_exit(2);
		}
	}
	return (number * sign);
}

static bool	is_first_arg_ok(char **arg)
{
	int	i;

	if (arg == NULL || arg[1] == NULL)
		return (false);
	i = -1;
	if (arg[1][0] == '-' || arg[1][0] == '+')
		++i;
	while (arg[1][++i] != '\0')
	{
		if (ft_isdigit(arg[1][i]) == false || i > 19)
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
