#ifndef EXEC_H
#define EXEC_H

#define CMD_LEFT  0
#define CMD_RIGHT 1

# define SET true
# define GET false

# include "../../includes/minishell.h"

typedef struct s_exec_data
{
    char *command_path;
    char **path_to_join;
}     t_exec_data;

char    *create_command_path(t_exec_data *data, t_command *command);
void    init_data(t_exec_data *data, t_command *command);
int     exec_command(t_command *command);
int     forking_node(t_command *node);
int     exec_sub_shell(t_command *node);
int     exec_builtin(t_command *node);
int     exec_and(t_command *node);
int     exec_or(t_command *node);
int     exec_single_command(t_command *command);
int     exec_single(t_command *command);
bool    is_built_in(t_command *node);
bool    should_fork(t_command *node);
void	ft_close(int *fd);
void	ft_pipe(int fd[2]);
void	ft_dup2(int *fd1, int fd2);
int		sig_event(void);
void    if_sigint(int sig);
void	set_parent_exec_signals(void);

#endif