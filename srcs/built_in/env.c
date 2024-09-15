/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:18:15 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/15 02:11:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	env(char **args)
{
	static t_env	*env = NULL;
	t_env_var		*temp;

	if (args[1] != NULL)
		return (print_err("env: too many args", false), EXIT_FAILURE);
	if (env == NULL)
		env = get_env_list(NULL);
	if (env == NULL || env->first == NULL)
		return (EXIT_SUCCESS);
	(void)args;
	temp = env->first;
	while (temp != NULL)
	{
		if (temp->value != NULL)
		{
			printf("%s=%s\n", temp->variable, temp->value);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

void	init_env(char **env_arg)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env) * 1);
	if (env == NULL)
		return (malloc_failed("init_env"));
	lock(env);
	if (env_arg == NULL || env_arg[0] == NULL)
	{
		(void)get_env_list(env);
		return ;
	}
	env->first = create_env(env_arg);
	if (env->first == NULL)
		return (ft_free(env));
	(void)get_env_list(env);
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
		return (malloc_failed("new_env_var"), NULL);
	if (variable != NULL)
	{
		new->variable = ft_strdup(variable);
		if (new->variable == NULL)
			return (ft_free(new), NULL);
		lock(new->variable);
	}
	else
		new->variable = NULL;
	if (value != NULL)
	{
		new->value = ft_strdup(value);
		if (new->value == NULL)
			return (ft_free(new->variable), ft_free(new), NULL);
		lock(new->value);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (lock(new), new);
}

t_env_var	*get_env_struct(char *variable)
{
	static t_env	*env = NULL;
	t_env_var		*node;

	if (env == NULL)
		env = get_env_list(NULL);
	if (env == NULL)
		return (NULL);
	node = env->first;
	while (node != NULL)
	{
		if (ft_strcmp(node->variable, variable) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
