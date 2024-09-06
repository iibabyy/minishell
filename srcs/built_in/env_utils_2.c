/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 02:13:15 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:41:11 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	*ft_getenv(char *var)
{
	t_env_var	*env;

	env = get_env_struct(var);
	if (env == NULL)
		return (NULL);
	return (env->value);
}

int	env_num(t_env *env)
{
	t_env_var	*var;
	int			i;

	if (env == NULL || env->first == NULL)
		return (0);
	i = 0;
	var = env->first;
	while (var != NULL)
	{
		++i;
		var = var->next;
	}
	return (i);
}

char	**env_tab(void)
{
	t_env		*env;
	t_env_var	*var;
	char		**res;
	int			i;

	env = get_env_list(NULL);
	if (env == NULL || env->first == NULL)
		return (NULL);
	if (env_num(env) == 0)
		return (NULL);
	res = ft_malloc(sizeof(char *) * env_num(env) + 1);
	if (res == NULL)
		return (malloc_failed("env_tab"), NULL);
	i = 0;
	var = env->first;
	while (var != NULL)
	{
		res[i] = multi_strjoin(3, var->variable, "=", var->value);
		if (res[i++] == NULL)
			return (free_2d_array((void ***)&res), NULL);
		var = var->next;
	}
	res[i] = NULL;
	return (res);
}
