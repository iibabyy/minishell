/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:18:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 21:01:38 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	add_env_var(t_env *env, t_env_var *new)
{
	t_env_var	*tmp;

	if (new == NULL)
		return ;
	if (env->first == NULL)
	{
		env->first = new;
		return ;
	}
	tmp = env->first;
	while (tmp->next != NULL)
	{
		if (tmp == new)
			return ;
		tmp = tmp->next;
	}
	if (tmp == new)
		return ;
	tmp->next = new;
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
	if (name == NULL)
		return (malloc_failed("env: variable_name"), NULL);
	lock(name);
	return (name);
}

char	*variable_value(char *env_line)
{
	char	*value;

	if (ft_strchr(env_line, '=') == NULL)
		return (NULL);
	value = ft_strdup(ft_strchr(env_line, '=') + 1);
	return (value);
}

t_env	*get_env_list(t_env *only_for_init)
{
	static t_env	*env = NULL;
	static bool		first = true;

	if (first == true)
	{
		env = only_for_init;
		first = false;
		return (NULL);
	}
	return (env);
}

void	destroy_var_node(t_env_var *node)
{
	ft_free(node->value);
	ft_free(node->variable);
	ft_free(node);
}
