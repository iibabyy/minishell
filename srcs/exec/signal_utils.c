/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:48:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 15:06:48 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void handle_sigint(int sig)
{
	printf("\n");
	g_signal = sig + 128;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigint_child(int sig)
{
    printf("\n");
    (void)sig;
}

void	null_sigint(int sig)
{
	(void)sig;
}

void quit_heredoc(int sig)
{
	g_signal = sig + 128;
	rl_done = 1;
	printf("\n");
	// rl_replace_line("", 0);
}
