#include "../../includes/minishell.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

#define LEFT_NODE 0
#define RIGHT_NODE 1

void	print_command(t_command *command);

bool	should_fork(t_command *node)
{
	if (node->type == SUB_SHELL || (node->type == COMMAND
			&& is_built_in(node) == false))
		return (true);
	return (false);
}

/*void ffcd(t_command *node, int pid[2], bool wait_lr[2],  int status[2])
{
	int	status;
	int	pid[2];

	if (should_fork(node->left))
	{
		pid[0] = forking_pipe_node(node->left,LEFT_NODE, fd);
		wait_lr[0] = true;
	}
	else
	{
		status[0] = exec_command(node->left);
		wait_lr[0] = false;
	}
	if (should_fork(node->right))
	{
		pid[1] = forking_pipe_node(node->right, RIGHT_NODE, fd);
		wait_lr[1] = true;
	}
	else
	{
		status[1] = exec_command(node->right);
		wait_lr[1] = false;
	}
}*/

int	forking_pipe_node(t_command *node, int pos, int fd[])
{
	int	pid;
	int	status;

	pid = ft_fork(node);
	if (pid == 0)
	{
		set_subshell_signals();
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
	ft_waitpid(pid[0], node);
	if (get_status() == 128 + SIGQUIT /*&& node->left->type*/)
	{
		if (node->previous && node->previous->type == PIPE)
			node->previous->sigquit = true;
		else
			node->sigquit = true;
	}
	ft_waitpid(pid[1], node);
	if (get_status() == 128 + SIGQUIT)
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
