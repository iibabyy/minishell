/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/15 18:29:42 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_AST(t_command *command);

// TODO: check all whitespaces, not only spaces

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_minishell(env);
	minishell();
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
