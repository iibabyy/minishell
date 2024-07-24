/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t final_size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	if (final_size <= ft_strlen(dst))
		return (final_size + ft_strlen(src));
	while (src[j] && i < final_size - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src + j));
}
