/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:43:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;
	int		size;

	if (src == NULL)
		return (NULL);
	size = ft_strlen((char *)src) + 1;
	str = ft_malloc(sizeof(char) * size);
	if (!str)
		return (malloc_failed("ft_strdup"), NULL);
	ft_strlcpy(str, src, size);
	return (str);
}
