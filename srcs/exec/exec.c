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

int	forking_pipe_node(t_command *node, int pos, int fd[])
{
	int	pid;
	int	status;

	
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
	return (pid);
}
int	exec_pipe(t_command *node)
{
	int	pid[2];
	int	status;
	int	fd[2];

	ft_pipe(fd);
	pid[0] = forking_pipe_node(node->left, LEFT_NODE, fd);
	pid[1] = forking_pipe_node(node->right, RIGHT_NODE, fd);
	ft_close(&fd[1]);
	ft_close(&fd[0]);
	(ft_close(&node->left->infile), ft_close(&node->right->infile));
	(ft_close(&node->left->outfile), ft_close(&node->right->outfile));
	waitpid(pid[0], &status, 0);
	set_exit_code(status);
	if (get_code(0, false) == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (get_code(0, false) == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	waitpid(pid[1], &status, 0);
	set_exit_code(status);
	if (get_code(0, false) == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (get_code(0, false) == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	return (get_code(0, false));
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
