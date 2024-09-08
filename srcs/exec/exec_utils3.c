#include "../../includes/minishell.h"
#include "exec.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

int exec_sub_shell(t_command *node)
{
	int pid;
	int status;
	t_command *command;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		open_redirections(node);
		ft_dup2(&node->infile, STDIN_FILENO);
		ft_dup2(&node->outfile, STDOUT_FILENO);
		command = parse(node->command[0]);
		if (command != NULL)
			status = exec(command);
		else
			status = EXIT_FAILURE;
		free_and_exit(status);
	}
	waitpid(pid, &status, 0);
	return(status);
}

int exec_builtin(t_command *node)
{
	char	**args;

	if(node->command == NULL)
		return (0);
	args = node->command;
	if(ft_strcmp("echo", args[0]) == 0)
		return(0);
	if(ft_strcmp("unset", args[0]) == 0)
		return (unset(args));
	if(ft_strcmp("cd", args[0]) == 0)
		return (cd(args));
	if(ft_strcmp("pwd", args[0]) == 0)
		return (pwd(args));
	if(ft_strcmp("export", args[0]) == 0)
		return (export(args));
	if(ft_strcmp("exit", args[0]) == 0)
		return (0);
	return(EXIT_FAILURE);
}

int forking_node(t_command *node)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
		status = exec_command(node);
		free_and_exit(status);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int exec_or(t_command *node)
{
	int status;

	if (should_fork(node->left))
		status = forking_node(node->left);
	else
		status = exec_command(node->left);
	if(status != 0)
	{
		if (should_fork(node->right))
			status = forking_node(node->right);
		else
			status = exec_command(node->right);
	}
	return(status);
}

int exec_and(t_command *node)
{
	int status;

	if (should_fork(node->left))
		status = forking_node(node->left);
	else
		status = exec_command(node->left);
	if(status == 0 && g_signal == 0)
	{
		if (should_fork(node->right))
			status = forking_node(node->right);
		else
			status = exec_command(node->right);
	}
	return(status);
}
