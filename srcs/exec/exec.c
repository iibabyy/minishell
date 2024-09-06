#include "../../includes/minishell.h"
#include "exec.h"
#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

void sigint_child(int sig);
void handle_sigint(int sig);

bool should_fork(t_command *node)
{
    if (node->type == SUB_SHELL
        || (node->type == COMMAND && is_built_in(node) == false))
        return (true);
    return (false);
}
int forking_node(t_command *node, t_exec_data *data)
{
    int pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        status = exec_command(node, data);
        exit(status);
    }
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

int exec_or(t_command *node, t_exec_data *data)
{
    int status;

    if (should_fork(node->left))
        status = forking_node(node->left, data);
    else
        status = exec_command(node->left, data);
    if(status != 0)
    {
        if (should_fork(node->right))
            status = forking_node(node->right, data);
        else
            status = exec_command(node->right, data);
    }
    return(status);
}

int exec_and(t_command *node, t_exec_data *data)
{
    int status;

    if (should_fork(node->left))
        status = forking_node(node->left, data);
    else
        status = exec_command(node->left, data);
    if(status == 0 && g_signal == 0)
    {
        if (should_fork(node->right))
            status = forking_node(node->right, data);
        else
            status = exec_command(node->right, data);
    }
    return(status);
}

void open_pipes_redirect(t_command *node)
{

    if(node == NULL)
        return ;
    open_pipes_redirect(node->left);
    open_pipes_redirect(node->right);
    if(node->type == COMMAND)
    {
        open_redirections(node);
    }
    return ;
}

int exec_pipe(t_command *node, t_exec_data *data)
{
    int status1 = 0;
    int status2 = 0;

    int pid[2];
    int fd[2];
    ft_pipe(fd);
    pid[0] = fork();
    if (pid[0] == 0)
    {
        set_child_signals();
        free((ft_close(&fd[0]), ft_dup2(&fd[1], STDOUT_FILENO), NULL));
        status1 = exec_command(node->left, data);
        exit(status1);
    }
    pid[1] = fork();
    if (pid[1] == 0)
    {
        set_child_signals();
        free((ft_close(&fd[1]), ft_dup2(&fd[0], STDIN_FILENO), NULL));
        status2 = exec_command(node->right, data);
        exit(status2);
    }
    (ft_close(&fd[0]), ft_close(&fd[1]));
    (ft_close(&node->left->infile), ft_close(&node->right->infile));
    (ft_close(&node->left->outfile), ft_close(&node->right->outfile));
    waitpid(pid[0], &status1, 0);
    waitpid(pid[1], &status2, 0);
    return (status2);
}

int exec_sub_shell(t_command *node, t_exec_data *data)
{
    int pid;
    int status;
    t_command *command;

    status = 0;
    pid = fork();
    if (pid == 0)
    {
		// set_parent_signals();
        open_redirections(node);
        ft_dup2(&node->infile, STDIN_FILENO);
        ft_dup2(&node->outfile, STDOUT_FILENO);
		command = parse(node->command[0]);
		if (command != NULL)
			status = exec_command(command, data);
        exit(status);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    return(status);
}
int exec_builtin(t_command *node)
{
    int status;

    status = 0;
    if(ft_strcmp("unset", node->command[0]) == 0)
        status = unset(node->command);
    // if(ft_strcmp("cd", node->command[0]) == 0)
    //     return (true);
    // if(ft_strcmp("pwd", node->command[0]) == 0)
    //     return (true);
    // if(ft_strcmp("ex", node->command[0]) == 0)
    //     return (true);
    // if(ft_strcmp("exit", node->command[0]) == 0)
        // fonction_exit(node->command[0]);
    return(status);
}
int exec_command(t_command *node, t_exec_data *data)
{
    int status = 0;

    if (node->type == COMMAND)
    {
        if (is_built_in(node))
            status = exec_builtin(node);
        else
            status = exec_single_command(node, data);
    }
    else if(node->type == OR)
        status = exec_or(node, data);
    else if(node->type == SUB_SHELL)
        status = exec_sub_shell(node, data);
    else if (node->type == AND)
        status = exec_and(node, data);
    else if (node->type == PIPE)
        status = exec_pipe(node, data);
    return (status);
}
