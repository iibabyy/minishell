/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:12:38 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/13 03:12:49 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"
#include "built_in.h"

bool	check_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		while (str[i])
		{
			if (str[i] == '-')
			{
				if (str[i + 1] != 'n')
					return (false);
			}
			if (str[i] != 'n' && str[i] != '-')
				return (false);
			i++;
		}
		return (true);
	}
	else
		return (false);
}

int	ft_check_args(char **args)
{
	int		j;
	bool	is_features;

	is_features = false;
	j = 0;
	while (args[j] && check_valid_flag(args[j]) == true)
	{
		is_features = true;
		j++;
	}
	print_2d_array(args + j);
	if (is_features != true)
	{
		printf("\n");
		return (0);
	}
	return (0);
}

int	echo_minishell(char **args)
{
	if (args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (args[1][0] == '-')
	{
		return (ft_check_args(args + 1));
	}
	else
	{
		print_2d_array(&args[1]);
		printf("\n");
	}
	return (0);
}
