/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:55:17 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/15 12:34:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_in/built_in.h"
#include "exec.h"

void	ft_dup2(int *fd1, int fd2)
{
	if (dup2(*fd1, fd2) == -1)
	{
		fprintf(stderr, "fd === %i\n", *fd1);
		perror("close");
		free_and_exit(1);
	}
	ft_close(fd1);
}

void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDERR_FILENO
		|| *fd == STDOUT_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		perror("close");
		free_and_exit(1);
	}
	*fd = -1;
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_and_exit(1);
	}
}

void	init_data(t_exec_data *data, t_command *command)
{
	data->path_to_join = ft_calloc(sizeof(char *), 1);
	if (data->path_to_join == NULL)
		free_and_exit(1);
	data->command_path = create_command_path(data, command);
}

int	ft_waitpid(int pid, t_command *command)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	set_status(status);
	if (command == NULL)
		return (get_status());
	if (get_status() == 128 + SIGINT)
		last_command(command)->sigint = true;
	if (get_status() == 128 + SIGQUIT)
		last_command(command)->sigquit = true;
	return (get_status());
}
