/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:33:28 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:41:46 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t el_count, size_t el_size)
{
	unsigned char	*buffer;

	buffer = ft_malloc(el_size * el_count);
	if (!buffer)
		return (malloc_failed("ft_calloc"), NULL);
	buffer = ft_memset(buffer, 0, (el_count * el_size));
	return (buffer);
}
