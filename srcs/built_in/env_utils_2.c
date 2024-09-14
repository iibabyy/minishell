/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 02:13:15 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:43:04 by mdembele         ###   ########.fr       */
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
	res = ft_malloc(sizeof(char *) * (env_num(env) + 1));
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

int	create_and_add_env_var(char *variable, char *value)
{
	t_env_var	*var;
	t_env		*env;

	env = get_env_list(NULL);
	if (env == NULL)
		return (EXIT_SUCCESS);
	var = get_env_struct(variable);
	if (var == NULL)
	{
		var = new_env_var(variable, value);
		if (var == NULL)
			return (EXIT_FAILURE);
		add_env_var(env, var);
	}
	else if (value != var->value)
	{
		var->value = value;
		lock(value);
	}
	return (EXIT_SUCCESS);
}

int	print_export_var(t_env *env)
{
	t_env_var	*var;

	var = env->first;
	while (var != NULL)
	{
		if (var->value != NULL)
			printf("export %s=\"%s\"\n", var->variable, var->value);
		else
			printf("export %s\n", var->variable);
		var = var->next;
	}
	return (EXIT_SUCCESS);
}
