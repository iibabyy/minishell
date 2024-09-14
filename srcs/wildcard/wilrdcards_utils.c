/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilrdcards_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:20:29 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 20:31:02 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*sort_wildcard_files(char *files)
{
	char	**temp;

	temp = ft_split(files, ' ');
	if (temp == NULL)
		return (ft_free(files), NULL);
	sort_str2d(temp);
	return (ft_free(files), str_join_2d_and_free(temp, " "));
}

bool	check_if_expand(char *str, char **temp)
{
	char	*wc;

	wc = ft_strchr(str, '*');
	while (wc != NULL)
	{
		if (!quotes_or_parenthesis_2d(temp, str, wc - str))
			return (true);
		wc = ft_strchr(++wc, '*');
	}
	return (false);
}

bool	is_valid_name(char *name, char *original, char **input)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (name == NULL || (ft_strncmp(name, ".", 1) == 0 && original[0] != '.'))
		return (false);
	while (original[i] != '\0')
	{
		if (original[i] == '*' && quotes_or_parenthesis_2d(input, original,
				i) == 0)
		{
			if (original[++i] == '\0')
				return (true);
			while (original[i] == '*')
				++i;
			while (name[j] != original[i] && name[j] != '\0')
				++j;
		}
		else
			if (name[j++] != original[i++])
				return (false);
	}
	return (true);
}
