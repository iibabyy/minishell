/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:08:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 11:28:12 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>

#include "structs.h"
#include "libft.h"
#include "garbage_collector.h"
#include "error.h"

extern volatile sig_atomic_t g_signal;

// minishell

# define MINISHELL_PROMPT "\033[0;32m➜  \033[0;36mminishell \033[0;33m✗\033[0m "

void		minishell(void);
int			init_minishell(char **env);
char		*minishell_prompt();

// features

int			init_aliases(void);
int			replace_aliases(t_command *last_command);
void		init_history(void);
void		ft_addhistory(char	*str);

// lexing

char		*replace_env_vars(char *input);
t_token		*input_to_tokens(char *input);
char		*get_input(char *end_of_file, char *prompt, bool quotes);

// parsing

t_command	*parse(char	*input);
int			open_redirections(t_command	*command);
t_command	*last_command(t_command *current);

// built-ins

int			alias(char **arg);
int			env(char **args);
char		**env_tab(void);
char		*ft_getenv(char *var);
void		init_env(char **env_arg);
int			unset(char **args);
int			export(char	**args);

// signals

void handle_sigint(int sig);
void quit_heredoc(int sig);
void sigint_child(int sig);

// debug

char 		*type_to_str(int type);
char		 *operator_type_to_str(int type);

#endif