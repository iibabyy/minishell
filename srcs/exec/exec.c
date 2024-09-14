/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:32:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 05:09:25 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

void	print_command(t_command *command);
void	exit_subshell(int sig);

void	redirect_subshell_signals(void)
{
	signal(SIGQUIT, exit_subshell);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, exit_subshell);
}

void	subsh_fd(int *arg, int sig)
{
	static int	*fd = NULL;

	if (fd == NULL)
		fd = arg;
	else
	{
		ft_close(&fd[0]);
		ft_close(&fd[1]);
		exit_subshell(sig);
	}
}

int	exec_single_built_in(t_command *command)
{
	int	fd[2];
	int	status;

	if (command->redirections)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (open_redirections(command) == EXIT_FAILURE)
			return (last_status_code(EXIT_FAILURE, SET), ft_close(&fd[0]),
				ft_close(&fd[1]), EXIT_FAILURE);
		else if (command->type == COMMAND
			&& ft_strcmp("exit", command->command[0]) == 0)
			(ft_close(&fd[0]), ft_close(&fd[1]));
		status = exec_single(command);
		if (fd[0] != -1)
			(dup2(fd[0], STDIN_FILENO), close(fd[0]));
		if (fd[1] != -1)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
	}
	else
		status = exec_single(command);
	return (status);
}

int	exec(t_command *command)
{
	int	status;

	if (command == NULL)
		return (EXIT_FAILURE);
	if (command->is_child == false)
		set_parent_exec_signals();
	if (command->type != COMMAND && command->type != SUB_SHELL)
		status = exec_command(command);
	else if (command->type == COMMAND && is_built_in(command) == true)
		status = exec_single_built_in(command);
	else
		status = exec_single(command);
	return (status);
}

int	forking_pipe_node(t_command *node, int pos, int fd[])
{
	int	pid;
	int	status;

	pid = ft_fork(node);
	if (pid == 0)
	{
		if (pos == LEFT_NODE)
		{
			ft_close(&fd[0]);
			ft_dup2(&fd[1], STDOUT_FILENO);
		}
		else
		{
			ft_close(&fd[1]);
			ft_dup2(&fd[0], STDIN_FILENO);
		}
		status = exec_command(node);
		free_and_exit(status);
	}
	return (pid);
}
