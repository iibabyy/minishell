/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:22:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/15 12:24:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

char	*check_command_status(t_command *command)
{
	struct stat	buf;

	if (stat(command->command[0], &buf) == -1)
		return (command->command[0]);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(command->command[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		free_and_exit(126);
	}
	if (command->command[0] == NULL || access(command->command[0], X_OK) == 0)
		return (command->command[0]);
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putendl_fd(command->command[0], 2);
		free_and_exit(126);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		print_err_and_exit(command->command[0], 127, false);
	}
	return (NULL);
}

char	*get_path(t_command *command, char **paths)
{
	int		i;
	char	*finalpath;

	i = -1;
	if (command->command[0] && ft_strchr(command->command[0], '/'))
		return (check_command_status(command));
	while (paths[++i])
	{
		paths[i] = ft_re_strjoin(paths[i], "/");
		if (!paths[i])
			print_err_and_exit(NULL, 1, false);
	}
	i = -1;
	while (paths[++i])
	{
		finalpath = ft_re_strjoin(paths[i], command->command[0]);
		if (!finalpath)
			print_err_and_exit(NULL, 1, false);
		if (access(finalpath, X_OK) == 0)
			return (finalpath);
	}
	ft_putstr_fd("minishell : command not found : ", 2);
	ft_putendl_fd(command->command[0], STDERR_FILENO);
	free_and_exit(127);
	return (NULL);
}

char	*create_command_path(t_exec_data *data, t_command *command)
{
	data->path_to_join = ft_split(ft_getenv("PATH"), ':');
	if (data->path_to_join == NULL)
	{
		data->command_path = ft_strdup(command->command[0]);
		return (data->command_path);
	}
	if (command && command->command)
		data->command_path = get_path(command, data->path_to_join);
	return (data->command_path);
}
