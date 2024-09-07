#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

void ft_dup2(int *fd1, int fd2)
{
	if (dup2(*fd1, fd2) == -1)
		exit(1);
    ft_close(fd1);
}

void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDERR_FILENO
		|| *fd == STDOUT_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		perror("close");
        exit(1);
	}
    *fd = -1;
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		exit(1);
}
void init_data(t_exec_data *data, t_command *command)
{
        data->path_to_join = ft_calloc(sizeof(char *), 1);
        if (data->path_to_join == NULL)
            exit(1);
        data->command_path = create_command_path(data , command);
}

bool is_built_in(t_command *node)
{
    if (node->command == NULL)
		return (false);
	if(ft_strcmp("echo", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("cd", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("pwd", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("unset", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("exit", node->command[0]) == 0)
        return (true);
    return(false);
}

int   exec_single_command(t_command *command, t_exec_data *exec)
{
    pid_t pid;
    int status = 0;

    pid = fork();
    if (pid == 0)
    {
        set_child_signals();
		init_data(exec, command);
        if (open_redirections(command) == EXIT_FAILURE)
            exit(EXIT_FAILURE);
        dup2(command->infile, STDIN_FILENO);
        dup2(command->outfile, STDOUT_FILENO);
        if (command->command == NULL || command->command[0] == NULL)
			exit (0);
		execve(exec->command_path, command->command, env_tab());
        ft_putstr_fd("minishell : command not found : ", 2);
        ft_putendl_fd(command->command[0], 2);
        exit(127);
    }
    else
      waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
