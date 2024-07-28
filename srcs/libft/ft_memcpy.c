/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:09 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/28 23:52:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned const char	*s;

	i = 0;
	s = src;
	while (n--)
	{
		ft_memset((dest + i), *(s + i), 1);
		i++;
	}
	return (dest);
}
