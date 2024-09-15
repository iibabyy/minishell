/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:14:36 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 19:45:16 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	forking_pipe_node(t_command *node, int pos, int fd[]);

bool	should_fork(t_command *node)
{
	if (node->type == SUB_SHELL || (node->type == COMMAND
			&& is_built_in(node) == false))
		return (true);
	return (false);
}

int	ft_fork(t_command *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		command->is_child = true;
		set_child_signals();
	}
	return (pid);
}

void	print_sig(void)
{
	int	status;

	status = get_status();
	if (status == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (status == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

int	exec_pipe(t_command *node)
{
	int	pid[2];
	int	fd[2];

	ft_pipe(fd);
	pid[0] = forking_pipe_node(node->left, LEFT_NODE, fd);
	pid[1] = forking_pipe_node(node->right, RIGHT_NODE, fd);
	(ft_close(&fd[1]), ft_close(&fd[0]));
	(ft_close(&node->left->infile), ft_close(&node->right->infile));
	(ft_close(&node->left->outfile), ft_close(&node->right->outfile));
	if (ft_waitpid(pid[0], node) != -1 && get_status() == 128 + SIGQUIT)
	{
		if (node->previous && node->previous->type == PIPE)
			node->previous->sigquit = true;
		else
			node->sigquit = true;
	}
	if (ft_waitpid(pid[1], node) != -1 && get_status() == 128 + SIGQUIT)
	{
		if (node->previous && node->previous->type == PIPE)
			node->previous->sigquit = true;
		else
			node->sigquit = true;
	}
	return (get_status());
}

int	exec_command(t_command *node)
{
	int	status;

	status = 0;
	if (node->type == COMMAND)
	{
		if (is_built_in(node))
			status = exec_builtin(node);
		else
			status = exec_single_command(node);
	}
	else if (node->type == OR)
		status = exec_or(node);
	else if (node->type == SUB_SHELL)
		status = exec_sub_shell(node);
	else if (node->type == AND)
		status = exec_and(node);
	else if (node->type == PIPE)
		status = exec_pipe(node);
	return (status);
}
