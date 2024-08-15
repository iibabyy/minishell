/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:09 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/15 17:49:45 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_env_var	*arg_to_env_var(char *arg);

int	export(char	**args)
{
	static t_env	*env = NULL;
	t_env_var		*new_var;
	int				i;

	if (env == NULL)
		env = get_env(NULL);
	if (env == NULL || env->first == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (args[++i] != NULL)
	{
		new_var = arg_to_env_var(args[i]);
		if (new_var == NULL)
			return (EXIT_FAILURE);
		add_env_var(env, new_var);
	}
	return (EXIT_SUCCESS);
}

static t_env_var	*arg_to_env_var(char *arg)
{
	t_env_var	*new_var;

	if (arg[0] != '_' && ft_isalpha(arg[0]) == 0)
		return (NULL);
	new_var = new_env_var(NULL, NULL);
	if (new_var == NULL)
		return (NULL);
	if (ft_strchr(arg, '=') != NULL)
	{
		new_var->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (new_var->value == NULL)
			return (ft_free(new_var), NULL);
		*ft_strchr(arg, '=') = '\0';
	}
	new_var->variable = ft_strdup(arg);
	if (new_var == NULL)
		return (ft_free(new_var->value), ft_free(new_var), NULL);
	return (new_var);
}
