/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:09:08 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/30 00:24:26 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int			i;
	int			size;
	const char	*str;

	i = 0;
	if (len >= ft_strlen(s + start))
		str = ft_malloc(sizeof(char) * ft_strlen(s + start));
	else
		str = ft_malloc(sizeof(char) * len);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
}
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (len > ft_strlen(s))
		size = ft_strlen(s);
	else
		size = len;
	if (size <= 0)
		return (NULL);
	str = ft_malloc(sizeof(char) * (size + 1));
	if (!s || !str)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < size)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
