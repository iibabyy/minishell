/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:19:25 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/13 03:41:30 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free_and_exit(ft_atoi(arg[1]) % 256);
	return (EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (is_whitespace(str[i]) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
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
