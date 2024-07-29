/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 15:11:49 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

char	*ft_re_strdup(char *src)
{
	char	*str;
	int		size;

	size = ft_strlen((char *)src) + 1;
	str = ft_malloc(sizeof(char) * size);
	if (!str)
		return (ft_free(src), NULL);
	ft_strlcpy(str, src, size);
	ft_free(src);
	return (str);
}
