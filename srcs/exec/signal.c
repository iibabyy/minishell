/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:47:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/06 20:16:38 by mdembele         ###   ########.fr       */
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
// int return_signal_code(int status,)