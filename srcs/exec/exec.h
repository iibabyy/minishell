/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:43:21 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 06:12:06 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define CMD_LEFT 0
# define CMD_RIGHT 1

# define SET 1
# define GET 0

# define LEFT_NODE 0
# define RIGHT_NODE 1

# include "../../includes/minishell.h"

typedef struct s_exec_data
{
	char	*command_path;
	char	**path_to_join;
}			t_exec_data;

char		*create_command_path(t_exec_data *data, t_command *command);
void		init_data(t_exec_data *data, t_command *command);
int			exec_command(t_command *command);
int			forking_node(t_command *node);
int			exec_sub_shell(t_command *node);
int			exec_builtin(t_command *node);
int			exec_and(t_command *node);
int			exec_or(t_command *node);
int			exec_single_command(t_command *command);
int			exec_single(t_command *command);
bool		is_built_in(t_command *node);
bool		should_fork(t_command *node);
void		ft_close(int *fd);
void		ft_pipe(int fd[2]);
void		ft_dup2(int *fd1, int fd2);
int			sig_event(void);
void		if_sigint(int sig);
void		set_parent_exec_signals(void);
void		set_status(int status);
void		set_subshell_signals(void);
int			ft_waitpid(int pid, t_command *command);
int			last_status_code(int status, bool setter);
int			ft_fork(t_command *command);
void		print_nl(void);
void		print_quit(void);
void		print_sig(void);
t_command	*parse_subshell(char *input);
t_token		*input_to_tokens_subshell(char *input);

#endif