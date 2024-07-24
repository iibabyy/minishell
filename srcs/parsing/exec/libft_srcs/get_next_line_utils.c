/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:56:21 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/05 20:00:16 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnlstrlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < destsize)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*ft_gnlstrjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	i;
	size_t	j;
	size_t	total;

	i = ft_str_len(s1, '\0');
	j = ft_str_len(s2, '\0');
	total = i + j + 1;
	strjoin = malloc(sizeof(char) * total);
	if (!(strjoin))
		return (free((char *)s1), NULL);
	ft_strlcpy(strjoin, s1, i + 1);
	ft_strlcpy(strjoin + i, (char *)s2, j + 1);
	free((char *)s1);
	return (strjoin);
}

char	*ft_gnlstrchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			return ((char *)s + 1);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_cpynl(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
