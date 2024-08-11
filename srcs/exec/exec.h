#ifndef EXEC_H
#define EXEC_H

#define CMD_LEFT  0
#define CMD_RIGHT 1
typedef struct s_exec_data
{
    char *command_path;
    char **path_to_join;
    int fd[2];
    int prev_fd[2];
    pid_t  pid_l;
    pid_t  pid_r;
}     t_exec_data;

char    *create_command_path(t_exec_data *data, t_command *command);
void    init_data(t_exec_data *data, t_command *command);
pid_t   exec_command(t_command *command, t_exec_data *data, bool pipeline);
void    exec_single_command(t_command *command);
void	ft_close(int *fd);
void	ft_pipe(int fd[2]);
void	ft_dup2(int *fd1, int fd2);

#endif