/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:06:03 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/04 22:24:11 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

int	replace_aliases(t_command *last_command)
{
	static char	***alias;

	if (alias == NULL)
	{
		alias = get_alias(NULL);
		if (alias == NULL)
			return (EXIT_SUCCESS);
	}
	if (last_command == NULL)
		return (EXIT_SUCCESS);
	if (check_if_alias(last_command, alias) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (replace_aliases(last_command->left) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (replace_aliases(last_command->right) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_if_alias(t_command *command, char ***aliases)
{
	int		i;
	int		type;
	char	**command_arr;

	i = -1;
	type = command->type;
	command_arr = command->command;
	while (aliases[++i] != NULL)
	{
		if (type != COMMAND || command_arr[0] == NULL)
			continue ;
		if (ft_strcmp(aliases[i][0], command_arr[0]) == 0)
		{
			command->command = insert_alias(command_arr, aliases[i]);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

int	init_aliases(void)
{
	char	***aliases;
	int		mshrc_fd;

	mshrc_fd = open(MSHRC, O_RDONLY);
	if (mshrc_fd == -1)
		return (error_log("init aliases:", true), EXIT_FAILURE);
	aliases = search_aliases(mshrc_fd);
	if (aliases == NULL)
		return (EXIT_FAILURE);
	get_alias(aliases);
	return (EXIT_SUCCESS);
}

char	***search_aliases(int fd)
{
	char	***aliases;
	char	*line;
	int		i;

	i = -1;
	aliases = ft_calloc(MAX_ALIAS + 1, sizeof(char **));
	if (aliases == NULL)
		return (NULL);
	while (++i < MAX_ALIAS)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "alias ", 6) == 0)
		{
			aliases[i] = line_to_alias(line);
		}
		ft_free(line);
	}
	aliases[i] = NULL;
	if (aliases[0] == NULL)
		return (ft_free(aliases), NULL);
	return (aliases);
}

char	**line_to_alias(char *line)
{
	char	**alias;
	int		i;
	int		start;

	i = 6;
	while (line[i] == ' ' && line[i] != '\0')
		++i;
	if (line[i] == '\0')
		return (NULL);
	start = i;
	while (line[i] != '=')
		if (ft_isalpha(line[i++]) == false)
			return (NULL);
	alias = ft_malloc(sizeof(char *) * (count_char(line + i + 2, ' ') + 3));
	if (alias == NULL)
		return (NULL);
	alias[0] = ft_substr(line, start, i - start);
	if (alias[0] == NULL)
		return (ft_free(alias), NULL);
	start = ++i;
	if (line[start] != '"')
		return (ft_free(alias[0]), ft_free(alias), NULL);
	alias = add_alias(alias, line, ++start);
	return (alias);
}
