/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:09:08 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:50:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		size = ft_strlen(s + start);
	else
		size = len;
	str = ft_malloc(sizeof(char) * (size + 1));
	if (!str)
		return (malloc_failed("ft_substr"), NULL);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
