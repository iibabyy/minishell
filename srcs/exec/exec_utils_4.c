/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:14:36 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 18:25:57 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	should_fork(t_command *node)
{
	if (node->type == SUB_SHELL || (node->type == COMMAND
			&& is_built_in(node) == false))
		return (true);
	return (false);
}

int	ft_fork(t_command *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		command->is_child = true;
		set_child_signals();
	}
	return (pid);
}

void	print_sig()
{
	int	status;

	status = get_status();
	if (status == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (status == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}
