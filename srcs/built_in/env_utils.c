# include "built_in.h"

void	add_env_var(t_env *env, t_env_var *new)
{
	if (new == NULL)
		return ;
	if (env->first == NULL)
	{
		env->first = new;
		return ;
	}
	new->next = env->first;
	env->first = new;
}

char	*variable_name(char *env_line)
{
	char	*name;
	size_t	i;

	if (env_line == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] != '=')
		++i;
	name = ft_substr(env_line, 0, i);
	return (name);
}

char	*variable_value(char *env_line)
{
	char	*value;

	value = ft_strdup(ft_strchr(env_line, '=') + 1);
	return (value);
}

t_env	get_env(t_env *only_for_init)
{
	static t_env	*env = NULL;

	if (env == NULL)
		return (env = only_for_init, NULL);
	return (env);
}

void	destroy_var_node(t_env_var *node)
{
	ft_free(node->value);
	ft_free(node->variable);
	ft_free(node);
}
