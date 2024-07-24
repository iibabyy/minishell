/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2d_array_nl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	print_2d_array_nl(char **NULL_TERMINATED_ARRAY)
{
	int	i;
	int	check;
	int	temp;

	i = 0;
	check = 0;
	while (NULL_TERMINATED_ARRAY[i])
	{
		temp = ft_putendl_fd(NULL_TERMINATED_ARRAY[i], 1);
		if (temp < 0)
			return (-1);
		check += temp;
		i++;
	}
	return (check);
}
