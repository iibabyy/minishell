/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:59 by mdembele          #+#    #+#             */
/*   Updated: 2024/06/08 13:36:29 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	ft_strwordlen(char const *str, char set)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

static size_t	ft_countword(char const *str, char set)
{
	int		i;
	size_t	nword;
	int		ammo;

	i = 0;
	nword = 0;
	ammo = 1;
	while (str[i])
	{
		if (ammo == 1 && str[i] != set)
		{
			nword++;
			ammo = 0;
		}
		if (str[i] == set)
			ammo = 1;
		i++;
	}
	return (nword);
}

static char	**exec(char **ssplit, char const *str, char set)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*str)
	{
		while (*str == set)
			str++;
		if (*str == '\0')
			break ;
		i = 0;
		ssplit[j] = malloc(sizeof(char) * ft_strwordlen(str, set) + 1);
		if (ssplit[j] == NULL)
		{
			while (j > 0)
				free(ssplit[--j]);
			free(ssplit);
			return (NULL);
		}
		while (*str != set && *str)
			ssplit[j][i++] = *(str++);
		ssplit[j++][i] = '\0';
	}
	ssplit[j] = (NULL);
	return (ssplit);
}

char	**ft_split(char const *str, char set)
{
	size_t	ntab;
	char	**ssplit;

	if (str == NULL)
	{
		ssplit = malloc(sizeof(char *));
		if (ssplit == NULL)
			return (NULL);
		ssplit[0] = NULL;
		return (NULL);
	}
	while (*str && *str == set)
		str++;
	ntab = ft_countword(str, set);
	ssplit = malloc((ntab + 1) * sizeof(char *));
	if (ssplit == NULL)
		return (NULL);
	ssplit = exec(ssplit, str, set);
	return (ssplit);
}
