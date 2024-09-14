/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:19:03 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 04:20:31 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	if_sigint(int sig)
{
	g_signal = 128 + sig;
	rl_done = 1;
	last_status_code(128 + sig, SET);
}

void	exit_subshell(int sig)
{
	free_and_exit(128 + sig);
}

void	set_subshell_signals(void)
{
	signal(SIGQUIT, exit_subshell);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, exit_subshell);
}
