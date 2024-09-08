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

int	forking_pipe_node(t_command *node, int pos)
{
	int	pid;
	int	status;
	int	fd[2];

	ft_pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
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
	ft_close(&fd[0]);
	ft_close(&fd[1]);
	return (pid);
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
int	exec_pipe(t_command *node)
{
	int	pid[2];
	int	status;

	pid[0] = forking_pipe_node(node->left, LEFT_NODE);
	pid[1] = forking_pipe_node(node->right, RIGHT_NODE);
	(ft_close(&node->left->infile), ft_close(&node->right->infile));
	(ft_close(&node->left->outfile), ft_close(&node->right->outfile));
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	return (status);
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
	get_code(status, SET);
	return (status);
}
