/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:09 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/22 14:54:37 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_env_var	*arg_to_env_var(char *arg);

int	export(char **args)
{
	static t_env	*env = NULL;
	t_env_var		*new_var;
	int				i;

	if (env == NULL)
		env = get_env_list(NULL);
	if (env == NULL)
		return (EXIT_SUCCESS);
	if (args[1] == NULL)
		return (print_export_var(env));
	i = 0;
	while (args[++i] != NULL)
	{
		parse_export_arg(args[i]);
		new_var = arg_to_env_var(args[i]);
		if (new_var == NULL)
			return (EXIT_FAILURE);
		add_env_var(env, new_var);
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

static t_env_var	*arg_to_env_var(char *arg)
{
	t_env_var	*new_var;
	char		*variable;
	char		*value;

	if (ft_strchr(arg, '=') != NULL)
	{
		value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (value == NULL)
			return (NULL);
		*ft_strchr(arg, '=') = '\0';
	}
	variable = ft_strdup(arg);
	if (variable == NULL)
		return (ft_free(value), NULL);
	new_var = get_env_struct(variable);
	if (new_var != NULL)
		ft_multi_free(2, new_var->value, variable);
	else
		new_var = new_env_var(variable, NULL);
	if (ft_strchr(arg, '=') != NULL)
		new_var->value = value;
	if (new_var == NULL)
		return (ft_free(value), ft_free(variable), NULL);
	return (new_var);
}

int	parse_export_arg(char *arg)
{
	int	i;

	i = 0;
	(void)arg;
	// if (arg[i] == ' ' || arg[i] == '\0')
	// 	return (print_err("export: wrong argument format", false),
	// 			EXIT_FAILURE);
	// if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	// 	return (print_err("export: wrong argument format", false),
	// 			EXIT_FAILURE);
	return (i);
}
