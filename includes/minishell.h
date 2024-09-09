/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:08:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/09 02:56:07 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define MINISHELL_H

# include "includes.h"

// minishell

int			init_minishell(char **env);
char		*minishell_prompt(void);
int			exec(t_command *command);

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
t_command	*last_command(t_command *current);
int			open_redirections(t_command	*command);

// built-ins

int			env(char **args);
char		**env_tab(void);
char		*ft_getenv(char *var);
void		init_env(char **env_arg);
int			unset(char **args);
int			export(char	**args);
int 		cd(char	**args);
int			pwd(char **arg);
char		*ft_getcwd(void);
int			ft_exit(char **arg);

// signals

void	set_parent_signals(void);
void	set_child_signals(void);
int		get_code(int error_code, bool setter);

// debug

char 		*type_to_str(int type);
char		 *operator_type_to_str(int type);

#endif