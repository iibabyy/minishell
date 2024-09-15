/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:09 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/15 02:11:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_env_var	*arg_to_env_var(char *arg);
static void			export_err(char identifier);

int	export(char **args)
{
	static t_env	*env = NULL;
	t_env_var		*new_var;
	int				i;
	int				status;

	if (env == NULL)
		env = get_env_list(NULL);
	if (env == NULL)
		return (EXIT_SUCCESS);
	if (args[1] == NULL)
		return (print_export_var(env));
	free((i = 0, status = EXIT_SUCCESS, NULL));
	while (args[++i] != NULL)
	{
		if (parse_export_arg(args[i]) == EXIT_FAILURE)
		{
			status = EXIT_FAILURE;
			continue ;
		}
		new_var = arg_to_env_var(args[i]);
		if (new_var == NULL)
			return (EXIT_FAILURE);
		add_env_var(env, new_var);
	}
	return (status);
}

char	*set_value(char *value)
{
	if (value == NULL)
		return (NULL);
	if (*value == '"')
	{
		value = ft_strtrim(value, "\"");
		if (value == NULL)
			return (NULL);
	}
	return (value);
}

static t_env_var	*arg_to_env_var(char *arg)
{
	t_env_var	*new_var;
	char		*variable;
	char		*value;

	value = NULL;
	if (ft_strchr(arg, '=') != NULL)
	{
		value = ft_strdup(ft_strchr(arg, '=') + 1);
		value = set_value(value);
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
	if (new_var == NULL)
		return (ft_free(value), ft_free(variable), NULL);
	lock((new_var->value = value, new_var));
	return (lock(new_var->value), lock(new_var->variable), new_var);
}

int	parse_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == false && arg[i] != '_')
		return (export_err(arg[i]), EXIT_FAILURE);
	++i;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == false && arg[i] != '_')
			return (export_err(arg[i]), EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

static void	export_err(char identifier)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putchar_fd(identifier, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}
