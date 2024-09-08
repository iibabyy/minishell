#include "../../includes/minishell.h"
#include "exec.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

void ft_dup2(int *fd1, int fd2)
{
	if (dup2(*fd1, fd2) == -1)
	{
		fprintf(stderr, "fd === %i\n", *fd1);
		perror("close");
        free_and_exit(1);
	}
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
        free_and_exit(1);
	}
    *fd = -1;
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
        free_and_exit(1);
	}
}

void init_data(t_exec_data *data, t_command *command)
{
        data->path_to_join = ft_calloc(sizeof(char *), 1);
        if (data->path_to_join == NULL)
            free_and_exit(1);
        data->command_path = create_command_path(data , command);
}
