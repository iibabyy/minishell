/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:10:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 20:26:43 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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
	char			*list;

	dir = opendir("./");
	if (dir == NULL)
		return (NULL);
	list = get_dir_files(dir, str, input);
	closedir(dir);
	if (list == NULL)
		return (NULL);
	return (list);
}

char	*get_dir_files(DIR *dir, char *str, char **input)
{
	struct dirent	*file;
	char			*list;

	free((list = NULL, file = readdir(dir), NULL));
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
				return (NULL);
		}
		list = ft_re_strjoin(list, file->d_name);
		if (list == NULL)
			return (NULL);
		file = readdir(dir);
	}
	if (list == NULL)
		return (str);
	return (sort_wildcard_files(list));
}
