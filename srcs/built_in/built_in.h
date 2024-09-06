/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:18:43 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 16:48:35 by ibaby            ###   ########.fr       */
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

int			parse_alias_arg(char *arg);
char		***init_new_aliases(void);
char		**create_alias(char *arg);
void		add_back_aliases(char ***aliases, char **alias);

int			parse_export_arg(char *arg);
int			print_export_var(t_env *env);

#endif