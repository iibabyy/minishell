/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:14:21 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 02:59:10 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] == c)
				i++;
		}
		if (s[i])
			i++;
	}
	count++;
	return (count);
}

char	*ft_strtrim2(char const *s1, char sep)
{
	char	*str;
	size_t	end;
	size_t	start;

	if (!s1)
		return (0);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && s1[start] == sep)
		start++;
	while (end > start && s1[end] == sep)
		end--;
	str = ft_substr(s1, start, (end - start + 1));
	return (str);
}

int	ft_split_2(const char *s, char **split, char sep, int words)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] == sep)
		i++;
	while (j < words)
	{
		start = i;
		while (s[i] != sep && s[i])
			i++;
		split[j] = ft_malloc(sizeof(char) * (i - start + 1));
		if (!split[j])
			return (malloc_failed("ft_split_2"), -1);
		ft_memmove(split[j], (s + start), (i - start));
		split[j][i - start] = '\0';
		while (s[i] == sep)
			i++;
		j++;
	}
	return (0);
}

char	**ft_split(const char *s, char sep)
{
	int		words;
	char	**split;
	int		check;

	if (s == NULL)
		return (NULL);
	words = count_words(s, sep);
	if (*s != '\0' && s[ft_strlen(s) - 1] == sep)
		words--;
	if (words < 0 || *s == '\0')
	{
		split = ft_malloc(sizeof(char *) * 1);
		if (!split)
			return (malloc_failed("ft_split"), NULL);
		split[0] = NULL;
		return (split);
	}
	split = ft_malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (malloc_failed("ft_split"), NULL);
	check = ft_split_2(s, split, sep, words);
	if (check == -1)
		return (free_2d_array((void ***)&split), NULL);
	split[words] = NULL;
	return (split);
}
