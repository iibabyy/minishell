/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:44:10 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 20:23:45 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*valuex;
	size_t			i;

	i = 0;
	valuex = pointer;
	while (count > 0)
	{
		valuex[i] = value;
		i++;
		count--;
	}
	return (valuex);
}
