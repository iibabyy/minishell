#include "../../includes/minishell.h"
#include "exec.h"
#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

int exec_or(t_command *node, t_exec_data *data)
{
    int status;

    status = exec_command(node->left, data);
    if(status != 0)
        status = exec_command(node->right, data);
    return(status);
}

int exec_and(t_command *node, t_exec_data *data)
{
    int status;

    status = exec_command(node->left, data);
    if(status == 0)
        status = exec_command(node->right, data);
    return(status);
}

int wait_all( t_exec_data *data, int i)
{
    int status;
    int j = 0;

    while (j <= i)
	{
		waitpid(data->pid[j], &status, 0);
		j++;
	}
    return(status);
}

int exec_pipe(t_command *node, t_exec_data *data)
{
    int status = 0;

    int pid[2];
    int fd[2];
    ft_pipe(fd);
    pid[0] = fork();
    if (pid[0] == 0)
    {
        free((ft_close(&fd[0]), ft_dup2(&fd[1], STDOUT_FILENO), NULL));
        status = exec_command(node->left, data);
        exit(status);
    }
    pid[1] = fork();
    if (pid[1] == 0)
    {
        free((ft_close(&fd[1]), ft_dup2(&fd[0], STDIN_FILENO), NULL));
        status = exec_command(node->right, data);
        exit(status);
    }
    free((ft_close(&fd[0]), ft_close(&fd[1]), NULL));
    free((ft_close(&node->left->infile), ft_close(&node->right->infile), NULL));
    free((ft_close(&node->left->outfile), ft_close(&node->right->outfile), NULL));
    free((waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0), NULL));
    return(status);
}

int exec_command(t_command *node, t_exec_data *data)
{
    int status = 0;

    if (node->type == COMMAND)
        status = exec_single_command(node, data);
    else if(node->type == OR)
        status = exec_or(node, data);
    else if (node->type == AND)
        status = exec_and(node, data);
    else if (node->type == PIPE)
        status = exec_pipe(node, data);
    else
        fprintf(stderr,"NULL NODE\n");
    return (status);
}
