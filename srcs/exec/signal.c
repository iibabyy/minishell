/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:47:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/13 04:20:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		sig_event(void);
void	if_sigint(int sig);
void	exit_subshell(int sig);
void	set_subshell_signals(void);

void	print_nl(void)
{
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_quit(void)
{
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	set_parent_exec_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	set_parent_signals(void)
{
	struct sigaction	sa;

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
	signal(SIGPIPE, exit_subshell);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_DFL);
}
