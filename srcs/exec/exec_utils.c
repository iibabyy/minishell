#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

void	ft_dup2(int *fd1, int fd2)
{
	if (dup2(*fd1, fd2) == -1)
		exit(1);
    fprintf(stderr, "DUP %d TO %d\n", *fd1, fd2);
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

void    exec_single_command(t_command *command)
{
    pid_t pid;
    t_exec_data *exec;
    int status;

    if (command == NULL)
        return;
    pid = fork();
    if (pid == 0)
    {
        exec = ft_calloc(1, sizeof(t_exec_data));
        if (exec == NULL)
            print_err_and_exit(NULL, 1, false);
        init_data(exec, command);
        open_redirections(command);
        ft_dup2(&command->infile, STDIN_FILENO);
        ft_dup2(&command->outfile, STDOUT_FILENO);
        execve(exec->command_path, command->command, NULL);     
    }
    else
    {
       waitpid(pid, &status, 0);
    }
}
