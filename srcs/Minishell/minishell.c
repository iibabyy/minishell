/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:41:11 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_command	*command;
	int			last_status;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	last_status = 0;
	init_minishell(envp);
	while (1)
	{
		set_parent_signals();
		str = get_line(last_status);
		if (g_signal != 0)
		{
			g_signal = 0;
			continue;
		}
		command = parse(str);
		last_status = exec(command);
	}
	return (0);
}
