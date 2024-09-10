#include "../../includes/minishell.h"
#include "exec.h"
#include "../built_in/built_in.h"
#include <unistd.h>

int exec_sub_shell(t_command *node)
{
    t_command    *command;

    set_subshell_signals();
    open_redirections(node);
    // ft_dup2(&node->infile, STDIN_FILENO);
    // ft_dup2(&node->outfile, STDOUT_FILENO);
    command = parse_subshell(node->command[0]);
    if (command == NULL)
        free_and_exit(EXIT_FAILURE);
    command->is_child = true;
    // if (should_fork(command))
    free_and_exit(exec(command));
    return (get_status());
}

int exec_builtin(t_command *node)
{
	char	**args;
	int		status;
	args = node->command;

    /*if (open_redirections(node) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
    dup2(node->infile, STDIN_FILENO);
    dup2(node->outfile, STDOUT_FILENO);*/
	// ft_close(&node->infile);
	// ft_close(&node->outfile);
	// set_child_signals();
	if (open_redirections(node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if(ft_strcmp("echo", args[0]) == 0)
		status = echo_minishell(args);
	if(ft_strcmp("unset", args[0]) == 0)
		status = unset(args);
	if(ft_strcmp("cd", args[0]) == 0)
		status = cd(args);
	if(ft_strcmp("pwd", args[0]) == 0)
		status = pwd(args);
	if(ft_strcmp("export", args[0]) == 0)
		status = export(args);
	if(ft_strcmp("env", args[0]) == 0)
		status = env(args);
	if(ft_strcmp("exit", args[0]) == 0)
	{
		if (node->is_child == false)
			ft_putendl_fd("exit", STDERR_FILENO);
		status = ft_exit(args);
	}
	last_status_code(status, SET);
	ft_close(&node->infile);
	ft_close(&node->outfile);
	return(status);
}

int forking_node(t_command *node)
{
	int pid;

	pid = ft_fork(node);
	if (pid == 0)
	{
		exec_command(node);
		free_and_exit(get_status());
	}
	ft_waitpid(pid, node);
	return (get_status());
}

int exec_or(t_command *node)
{
    int status;

    if (should_fork(node->left))
        status = forking_node(node->left);
    else
        status = exec_command(node->left);
    status = get_status();
    if (get_status() == 128 + SIGQUIT)
    {
		last_command(node)->sigquit = false;
        ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
    }
    if((status != 0 && status <= 128) || status == 128 + SIGQUIT)
    {
        if (should_fork(node->right))
            status = forking_node(node->right);
        else
            status = exec_command(node->right);
        if (get_status() == 128 + SIGQUIT)
        {
            if (node->previous && node->previous->type == PIPE)
                node->previous->sigquit = true;
            else
                node->sigquit = true;
        }
    }
    return(get_status());
}

int exec_and(t_command *node)
{
	int status;

	if (should_fork(node->left))
		status = forking_node(node->left);
	else
		status = exec_command(node->left);
	status = get_status();
	if (get_status() == 128 + SIGQUIT)
	{
		if (node->previous && node->previous->type == PIPE)
			node->previous->sigquit = true;
		else
			node->sigquit = true;
	}
	if(status == 0)
	{
		if (should_fork(node->right))
			status = forking_node(node->right);
		else
			status = exec_command(node->right);
		if (get_status() == 128 + SIGQUIT)
		{
			if (node->previous && node->previous->type == PIPE)
				node->previous->sigquit = true;
			else
				node->sigquit = true;
		}
	}
	return(get_status());
}
