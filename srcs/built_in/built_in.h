/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:18:43 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:57:10 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../../includes/minishell.h"

t_env_var	*create_env(char **env);
t_env_var	*new_env_var(char *variable, char *value);
void		add_env_var(t_env *env, t_env_var *new);
char		*variable_name(char *env_line);
char		*variable_value(char *env_line);
t_env		*get_env_list(t_env *only_for_init);
void		destroy_var_node(t_env_var *node);
void		delete_env_var(t_env *env, t_env_var *var);
t_env_var	*get_env_struct(char *variable);
char		*ft_getenv(char *var);
int			cd_error(char *err, bool erno);
int			create_and_add_env_var(char *variable, char *value);
char		*ft_getcwd(void);
int			update_pwd(char *old_pwd);
int			parse_export_arg(char *arg);
int			print_export_var(t_env *env);
int			echo_minishell(char **args);
int			print_export_var(t_env *env);

#endif