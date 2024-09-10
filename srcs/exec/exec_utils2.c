#include "exec.h"
#include "../built_in/built_in.h"

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

int    ft_waitpid(int pid, t_command *command)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
        return (EXIT_FAILURE);
    set_status(status);
	if (command == NULL)
		return (get_status());
    if (get_status() == 128 + SIGINT)
        last_command(command)->sigint = true;
    if (get_status() == 128 + SIGQUIT)
        last_command(command)->sigquit = true;
    return (get_status());
}

int	ft_fork(t_command *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		command->is_child = true;
		set_child_signals();
	}
	return (pid);
}

void	print_sig()
{
	int	status;

	status = get_status();
	if (status == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (status == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}
