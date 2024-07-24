/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:03 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/19 22:52:56 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *str, int tofind, size_t n)
{
	unsigned const char	*s;

	s = str;
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)tofind)
		{
			return ((unsigned char *)s);
		}
		s++;
	}
	return (0);
}
