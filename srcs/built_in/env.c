# include "built_in.h"

void	init_env(char **env_arg)
{
	t_env		*env;

	if (env_arg == NULL)
		return ;
	env = ft_malloc(sizeof(t_env) * 1);
	if (env == NULL)
		return (NULL);
	env->first = create_env(env_arg);
	if (env->first == NULL)
		return (ft_free(env));
	(void)get_env(env);
}

t_env_var	*create_env(char **env)
{
	t_env_var	*first;
	t_env_var	*temp;
	int			i;

	i = 0;
	first = new_env_var(variable_name(env[i]), variable_value(env[i]));
	if (first == NULL)
		return (NULL);
	temp = first;
	while (env[++i] != NULL)
	{
		temp->next = new_env_var(variable_name(env[i]), variable_value(env[i]));
		if (temp->next == NULL)
			return (NULL);
		if (env[i] == NULL)
			break;
		temp = temp->next;
	}
	temp->next = NULL;
	return (first);
}

t_env_var	*new_env_var(char *variable, char *value)
{
	t_env_var	*new;

	new = ft_malloc(sizeof(t_env_var) * 1);
	if (new == NULL)
		return (NULL);
	new->variable = ft_strdup(variable);
	if (new->variable == NULL)
		return (ft_free(new), NULL);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		return (ft_free(new->variable), ft_free(new), NULL);
	new->next = NULL;
	return (new);
}
