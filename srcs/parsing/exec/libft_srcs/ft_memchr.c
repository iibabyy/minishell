/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:45:28 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/21 19:28:24 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = (const unsigned char *)s;
	unsigned char		uc;
	size_t				num;

	uc = (unsigned char)c;
	num = 0;
	while (num < n)
	{
		if (str[num] == uc)
			return ((void *)(str + num));
		num++;
	}
	return (NULL);
}
