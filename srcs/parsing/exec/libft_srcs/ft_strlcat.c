/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:13 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 23:02:56 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	sizedest;
	size_t	sizesrc;
	size_t	i;
	size_t	j;

	sizedest = ft_strlen(dest);
	sizesrc = ft_strlen(src);
	if (size <= sizedest)
		return (size + sizesrc);
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (i < (size - 1) && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (sizedest + sizesrc);
}
