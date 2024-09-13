/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:16 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:58:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	unset(char **args)
{
	static t_env	*env = NULL;
	t_env_var		*node;
	int				i;

	if (env == NULL)
		env = get_env_list(NULL);
	if (env == NULL || env->first == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (args[++i] != NULL)
	{
		node = get_env_struct(args[i]);
		if (node == NULL)
			continue ;
		if (ft_strcmp(args[i], node->variable) == 0)
			delete_env_var(env, node);
	}
	return (EXIT_SUCCESS);
}

void	delete_env_var(t_env *env, t_env_var *var)
{
	t_env_var	*temp;

	if (env == NULL || env->first == NULL || var == NULL)
		return ;
	temp = env->first;
	if (temp == var)
	{
		env->first = var->next;
		return (destroy_var_node(var));
	}
	while (temp->next != NULL)
	{
		if (temp->next == var)
		{
			temp->next = var->next;
			return (destroy_var_node(var));
		}
		temp = temp->next;
	}
}
