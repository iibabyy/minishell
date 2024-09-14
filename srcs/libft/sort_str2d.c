/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:05:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 20:30:41 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	sort_str2d(char **str)
{
	int		temp;
	char	*lower;
	int		i;
	int		y;

	y = -1;
	while (str[++y] != NULL)
	{
		i = y;
		temp = i;
		lower = str[i];
		while (str[++i] != NULL)
		{
			if (ft_strcmp(lower, str[i]) > 0)
			{
				temp = i;
				lower = str[i];
			}
		}
		str[temp] = str[y];
		str[y] = lower;
	}
}
