#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "../../includes/structs.h"
#include "../../includes/libft.h"

t_env_var	*create_env(char **env);
t_env_var	*new_env_var(char *variable, char *value);
void		add_env_var(t_env *env, t_env_var *new);
char		*variable_name(char *env_line);
char		*variable_value(char *env_line);
t_env		get_env(t_env *only_for_init);
void		destroy_var_node(t_env_var *node);

#endif