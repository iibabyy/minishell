/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:08:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/26 16:53:26 by ibaby            ###   ########.fr       */
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

// minishell

void		minishell(void);
int			init_minishell(char **env);

// features

int			init_aliases();
int			replace_aliases(t_command *last_command);

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
void		init_env(char **env_arg);
int			env(char **args);
int			unset(char **args);
int			export(char	**args);


// debug

char 		*type_to_str(int type);
char		 *operator_type_to_str(int type);

#endif