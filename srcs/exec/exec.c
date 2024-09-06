#include "../../includes/minishell.h"
#include "exec.h"
#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

void sigint_child(int sig);
void handle_sigint(int sig);

int exec_or(t_command *node, t_exec_data *data)
{
    int status;

    status = exec_command(node->left, data);
    if(WEXITSTATUS(status) != 0)
        status = exec_command(node->right, data);
    return(status);
}

int exec_and(t_command *node, t_exec_data *data)
{
    int status;

    status = exec_command(node->left, data);
    if(WEXITSTATUS(status) == 0)
        status = exec_command(node->right, data);
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
    signal(SIGINT, &sigint_child);
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

// int exec_sub_shell(t_command *node, t_exec_data *data)
// {
// 	int pid;
// 	int status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
		
// 	}
// 	else
// 		waitpid(pid, &status, 0);
// }

int exec_command(t_command *node, t_exec_data *data)
{
    int status = 0;

    if (node->type == COMMAND)
        status = exec_single_command(node, data);
    else if(node->type == OR)
        status = exec_or(node, data);
	// else if(node->type == SUB_SHELL)
	// 	status = exec_sub_shell(node, data);
    else if (node->type == AND)
        status = exec_and(node, data);
    else if (node->type == PIPE)
        status = exec_pipe(node, data);
    return (status);
}
