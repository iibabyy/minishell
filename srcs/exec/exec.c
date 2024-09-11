#include "../../includes/minishell.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

#define LEFT_NODE 0
#define RIGHT_NODE 1

void	print_command(t_command *command);

int	exec_single_built_in(t_command *command)
{
	int	fd[2];
	int	status;

	if(command->redirections)
	{
		pipe(fd);
		dup2(STDIN_FILENO, fd[0]);
		dup2(STDOUT_FILENO, fd[1]);
		open_redirections(command);
		status = exec_single(command);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		open_redirections(command);
		status = exec_single(command);
	}
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
