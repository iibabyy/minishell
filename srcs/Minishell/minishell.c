/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 02:26:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FILENO) == 0)
		free_and_exit(2);
	set_parent_signals();
	init_minishell(envp);
	while (1)
	{
		clear_garbage();
		set_parent_signals();
		minishell();
	}
	return (0);
}

void	minishell(void)
{
	struct termios	term;
	t_command	*command;
	char		*str;

	str = get_line();
	if (g_signal != 0)
	{
		g_signal = 0;
		return ;
	}
	command = parse(str);
	if (command == NULL)
		return ;
	(tcgetattr(STDOUT_FILENO, &term));
	exec(command);
	(tcsetattr(STDOUT_FILENO, TCSANOW, &term));
	if (command->sigint == true)
		print_nl();
	else if (command->sigquit == true)
		print_quit();
}
