# include "built_in.h"

int	export(char	** args)
{
	static t_env	*env = NULL;
	t_env_var		*new_var;
	int				i;

	if (env == NULL)
		env = get_env(NULL);
	if (env == NULL || env->first == NULL)
		return (EXIT_SUCCESS);
	i = -1;
	while (args[++i] != NULL)
	{
		new_var = new_env_var(NULL, NULL);
		if (new_var == NULL)
			return (EXIT_FAILURE);
		if (ft_strchr(args[i], '=') != NULL)
		{
			new_var->value = ft_strdup(ft_strchr(args[i], '='));
			if (new_var->value == NULL)
				return (ft_free(new_var), EXIT_FAILURE);
			*ft_strchr(args[i], '=') = '\0';
		}
		new_var->variable = ft_strdup(args[i]);
		if (new_var == NULL)
			return (ft_free(new_var->value), ft_free(new_var), EXIT_FAILURE);
		add_env_var(env, new_var);
	}
	return (EXIT_SUCCESS);
}
