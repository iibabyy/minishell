/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:47:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/09 03:38:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int    sig_event(void)
{
    return (EXIT_SUCCESS);
}

void    if_sigint(int sig)
{
    g_signal = 128 + sig;
    rl_done = 1;
	get_code(g_signal, SET);
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

void	set_parent_exec_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
}

void	set_parent_signals(void)
{
	struct sigaction    sa;

	g_signal = 0;
    rl_event_hook = sig_event;
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = if_sigint;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void	set_child_signals(void)
{
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, SIG_DFL);
}
