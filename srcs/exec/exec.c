#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>


void exec_node(t_command *node, t_exec_data *data, int lr_flag)
{
    if (lr_flag == CMD_LEFT)
    {
        ft_close(&data->fd[0]);
        ft_dup2(&data->fd[1], STDOUT_FILENO);
        open_redirections(node);
    }
    else if (lr_flag == CMD_RIGHT)
    {
        ft_close(&data->fd[1]);
        ft_dup2(&data->fd[0], STDIN_FILENO);
        open_redirections(node);
    }
    ft_putendl_fd(data->command_path, 2);
    execve(data->command_path, node->command, NULL);
}

void execute_lr_command (t_command *left_node, t_command *right_node)
{
    t_exec_data *data;
    int         status;

    data = ft_calloc(sizeof(t_exec_data), 1);
    ft_pipe(data->fd);
    data->pid_l = fork();
    if (data->pid_l == 0)
    {
        init_data(data, left_node);
        exec_node(left_node, data, CMD_LEFT);
    }
    else
    {
        data->pid_r = fork();
        if (data->pid_r == 0)
        {
            init_data(data, right_node);
            exec_node(right_node, data, CMD_RIGHT);
        }
        else
        {
            ft_close(&data->fd[0]);
            ft_close(&data->fd[1]);
            waitpid(data->pid_l, &status, 0);
            waitpid(data->pid_r, &status, 0);
        }
    }
}



pid_t exec_command(t_command *node, bool pipeline)
{

    
   if (node == NULL)
        return (0);
   if (node->type == COMMAND)
   {
       if (pipeline == false)
            exec_single_command(node);
   }
    
   if (node->type == PIPE)
   {
        execute_lr_command(node->left, node->right);
        exec_command(node->previous, false);
   }
   return (0);
}