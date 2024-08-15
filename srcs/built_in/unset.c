# include "built_in.h"

int	unset(char **args)
{
	static t_env	*env;
	t_env_var		*temp;
	int				i;

	if (env == NULL)
		env = get_env(NULL);
	if (env == NULL || env->first == NULL)
		return (EXIT_SUCCESS);
	// if (parse_unset_args(args) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	i = -1;
	while (args[++i] != NULL)
	{
		temp = env->first;
		while (temp != NULL)
		{
			if (ft_strcmp(args[i], temp->variable) == 0)
			{
				delete_env_var(env, temp);
			}
			temp = temp->next;
		}
	}
	return (EXIT_SUCCESS);
}

void	delete_env_var(t_env *env, t_env_var *var)
{
	t_env_var	*temp;

	if (env == NULL || env->first == NULL)
		return (NULL);
	temp = env->first;
	if (temp == var)
	{
		env->first = var->next;
		return (destroy_var_node(var));
	}
	while (temp->next != NULL)
	{
		if (temp->next = var)
		{
			temp->next = var->next;
			return (destroy_var_node(var));
		}
		temp = temp->next;
	}
}
