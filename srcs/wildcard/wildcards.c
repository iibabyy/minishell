/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:10:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 05:51:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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

char	*expand_wildcard(char *input)
{
	char	**temp;
	int		i;

	if (count_char(input, '*') == 0)
		return (input);
	temp = ft_split(input, ' ');
	if (temp == NULL)
		return (NULL);
	i = -1;
	while (temp[++i] != NULL)
	{
		if (check_if_expand(temp[i], temp) == false)
			continue ;
		temp[i] = list_files(temp[i], temp);
		if (temp[i] == NULL)
			return (free_2d_array((void ***)&temp), NULL);
	}
	return (str_join_2d_and_free(temp, " "));
}

char	*list_files(char *str, char **input)
{
	DIR				*dir;
	struct dirent	*file;
	char			*list;

	dir = opendir("./");
	if (dir == NULL)
		return (NULL);
	list = NULL;
	file = readdir(dir);
	while (file != NULL)
	{
		if (is_valid_name(file->d_name, str, input) == false)
		{
			file = readdir(dir);
			continue ;
		}
		if (list != NULL)
		{
			list = ft_re_strjoin(list, " ");
			if (list == NULL)
				return (closedir(dir), NULL);
		}
		list = ft_re_strjoin(list, file->d_name);
		if (list == NULL)
			return (closedir(dir), NULL);
		file = readdir(dir);
	}
	if (list == NULL)
		return (closedir(dir), str);
	return (closedir(dir), list);
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
