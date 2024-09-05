/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:47:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/06 00:12:52 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sigint(int sig)
{
	printf("\n");
	g_signal = sig + 128;
	// rl_done = 1;
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
