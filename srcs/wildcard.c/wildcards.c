/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:57:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/11 17:57:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

// char	*next_depth(char *path);
// bool	is_valid_name(char *name, char *to_find);
// char	**list_files(char *dirname, char *to_find);

// char	*replace_wildcard(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (need_ == true)
// 	{
// 		if (str == NULL || count_char(str, '*') == 0)
// 			return (str);
	
// 	}
// 	return (str);
// }

// char	**list_files(char *dirname, char *to_find)
// {
// 	DIR				*dir;
// 	struct dirent	*file;
// 	char			**list;
// 	char			*temp[2];

// 	list = NULL;
// 	if (to_find == NULL || (dir = opendir(dirname)) == NULL)
// 		return (printf("error 1\n"), NULL);
// 	while ((file = readdir(dir)) != NULL)
// 	{
// 		if (is_valid_name(file->d_name, to_find) == false)
// 			continue ;
// 		if (file->d_type == DT_DIR)
// 		{
// 			list = str2djoin_and_free(list, list_files(file->d_name, next_depth(to_find)));
// 			if (list == NULL)
// 				return (printf("error 2\n"), NULL);
// 		}
// 		else
// 		{
// 			temp[0] = file->d_name;
// 			temp[1] = NULL;
// 			list = str2djoin_and_free(list, temp);
// 			if (list == NULL)
// 				return (printf("error 3\n"), NULL);
// 		}
// 		printf("P:\n");
// 		print_2d_array_nl(temp);
// 		printf("\n\n");
// 	}
// 	return (list);
// }

// char	*next_depth(char *path)
// {
// 	if (path == NULL)
// 		return (printf("error 0.1\n"), NULL);
// 	if (ft_strchr(path, '/') == NULL)
// 		return (printf("error 0.2\n"), NULL);
// 	else
// 		return (ft_strdup(&ft_strchr(path, '/')[1]));
// }

// bool	is_valid_name(char *name, char *to_find)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	printf("is_valid_name: to_find: %s: ", to_find);
// 	while (to_find[i] != '\0'&& to_find[i] != '/')
// 	{
// 		if (to_find[i] == '*')
// 		{
// 			++j;
// 			if (to_find[++i] == '/')
// 				return (true);
// 			while (name[++j] != to_find[i] && name[j] != '\0')
// 				;
// 		}
// 		else if (name[++j] != to_find[i])
// 			return (printf("%s: error 1.1\n", name), false);
// 	}
// 	return (true);
// }

// char	*first_dir_name(char *path)
// {
// 	int		i;
	
// 	if (path == NULL)
// 		return (printf("error 2.0\n"), NULL);
// 	if (path[0] == '/')
// 		return (ft_strdup("/"));
// 	i = -1;
// 	while (path[++i] != '\0')
// 	{
// 		if (path[i] == '/')
// 			return (ft_substr(path, 0, i));
// 	}
// 	return (ft_strdup(path));
// }
