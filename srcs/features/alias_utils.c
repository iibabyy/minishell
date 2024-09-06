/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:24:38 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 17:01:33 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

void	clear_3d_array(char ***alias, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free_2d_array((void ***)&alias[i]);
		++i;
	}
	ft_free((void *)alias);
}

char	***get_alias(char ***init_alias)
{
	static char	***alias = NULL;

	if (alias == NULL)
	{
		alias = init_alias;
		return (NULL);
	}
	else
		return (alias);
}

char	**add_alias(char **array, char *line, int start)
{
	char	**alias_val;
	int		i;

	i = 0;
	while (line[start + i] != '\n' && line[start + i] != '\0')
	{
		if (line[start + i] == '\n' || line[start + i] == '\0')
			return (NULL);
		if (line[start + i] == '"')
			break ;
		++i;
	}
	line[start + i] = '\0';
	alias_val = ft_split(line + start, ' ');
	if (alias_val == NULL)
		return (ft_free(alias_val),
			error_log("add_alias: ft_split failed:", true), NULL);
	i = 0;
	while (alias_val[i] != NULL)
	{
		array[i + 1] = alias_val[i];
		++i;
	}
	array[i + 1] = NULL;
	return (ft_free(alias_val), array);
}

char	**insert_alias(char **command, char **alias)
{
	char	**new_command;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_command = ft_malloc(sizeof(char *)
			* (ft_strlen_2d(command) + ft_strlen_2d(alias)));
	if (new_command == NULL)
		return (command);
	while (alias[++i + 1] != NULL)
		new_command[i] = alias[i + 1];
	while (command[++j + 1] != NULL)
		new_command[i + j] = command[j + 1];
	new_command[i + j] = NULL;
	ft_free(command);
	return (new_command);
}
