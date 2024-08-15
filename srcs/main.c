/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/15 20:12:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_AST(t_command *command);

// TODO: check all whitespaces, not only spaces

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_minishell(envp);
	// minishell();
	char *str;
	char **arg;
	t_command *command;
	while (1)
	{
		str = readline("\033[0;36mminishell \033[0;33m✗\033[0m ");
		add_history(str);
		str = replace_env_vars(str);
		arg = ft_split(str, ' ');
		if (arg[0] == NULL)
			continue ;
		printf("%s:\n\n", str);
		if (ft_strcmp(arg[0], "export") == 0)
			export(arg);
		else if (ft_strcmp(arg[0], "unset") == 0)
			unset(arg);
		else if (ft_strcmp(arg[0], "alias") == 0)
			alias(arg);
		else if (ft_strcmp(arg[0], "env") == 0)
			env(arg);
		else if (ft_strcmp(arg[0], "exit") == 0)
		{
			free(str);
			destroy_garbage(NULL);
			exit(EXIT_SUCCESS);
		}
		else
		{
			command = parse(str);
			print_AST(command);
		}
		free(str);
		free_2d_array((void ***)&arg);
	}
	return (0);
}

void	minishell(void)
{
	t_command	*command;
	char		*str;

	while (1)
	{
		str = readline("\033[0;36mminishell \033[0;33m✗\033[0m ");
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			break ;
		}
		command = parse(str);
		if (command == NULL)
			return (free(str));
		print_AST(command);
		free(str);
	}
	destroy_garbage(NULL);
}

int	init_minishell(char **env)
{
	ft_malloc(0);
	init_aliases();
	init_error_log();
	init_env(env);
	return (EXIT_SUCCESS);
}
