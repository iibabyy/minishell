/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:14:39 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/30 01:14:31 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	count_char_2d(char **array, char char_to_count)
{
	int	x;
	int	y;
	int	count;

	y = -1;
	count = 0;
	while (array[++y] != NULL)
	{
		x = -1;
		while (array[y][++x] != '\0')
		{
			if (array[y][x] == char_to_count)
				++count;
		}
	}
	return (count);
}
