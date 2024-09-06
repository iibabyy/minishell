#ifndef EXEC_H
#define EXEC_H

#define CMD_LEFT  0
#define CMD_RIGHT 1

# include "../../includes/minishell.h"

typedef struct s_exec_data
{
    char *command_path;
    char **path_to_join;
    int fd[2];
    int prev_fd[2];
    bool end;
    pid_t  pid_l;
    pid_t  *pid;
    pid_t  pid_r;
    char    **envp;
}     t_exec_data;

char    *create_command_path(t_exec_data *data, t_command *command);
void    init_data(t_exec_data *data, t_command *command);
int   exec_command(t_command *command, t_exec_data *data);
int   exec_single_command(t_command *command, t_exec_data *exec);
void	ft_close(int *fd);
void	ft_pipe(int fd[2]);
void	ft_dup2(int *fd1, int fd2);
void	sigint_child(int sig);
void	handle_sigint(int sig);
void	null_sigint(int sig);
void	handle_sigint(int sig);
void	quit_heredoc(int sig);
void 	sigint_child(int sig);
int		sig_event(void);
void    if_sigint(int sig);

#endif