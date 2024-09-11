/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/12 00:31:56 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_command	*command;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_minishell(envp);
	while (1)
	{
		set_parent_signals();
		clear_garbage();
		str = get_line();
		if (g_signal != 0)
		{
			g_signal = 0;
			continue;
		}
		command = parse(str);
		if (command == NULL)
			continue ;
		//print_AST(command);
		exec(command);
		if (command->sigint == true)
			print_nl();
		else if (command->sigquit == true)
			print_quit();
	}
	return (0);
}
