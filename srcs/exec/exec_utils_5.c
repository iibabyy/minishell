/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:53:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 05:03:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	left_and(t_command *node)
{
	if (should_fork(node->left))
		forking_node(node->left);
	else
		exec_command(node->left);
	if (get_status() == 128 + SIGQUIT)
	{
		if (node->previous && node->previous->type == PIPE)
			node->previous->sigquit = true;
		else
			node->sigquit = true;
	}
}

int	exec_and(t_command *node)
{
	int	status;

	left_and(node);
	status = get_status();
	if (status == 0)
	{
		if (should_fork(node->right))
			status = forking_node(node->right);
		else
			status = exec_command(node->right);
		if (get_status() == 128 + SIGQUIT)
		{
			if (node->previous && node->previous->type == PIPE)
				node->previous->sigquit = true;
			else
				node->sigquit = true;
		}
	}
	return (get_status());
}

void	left_or(t_command *node)
{
	if (should_fork(node->left))
		forking_node(node->left);
	else
		exec_command(node->left);
	if (get_status() == 128 + SIGQUIT)
	{
		last_command(node)->sigquit = false;
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

int	exec_or(t_command *node)
{
	int	status;

	left_or(node);
	status = get_status();
	if ((status != 0 && status <= 128) || status == 128 + SIGQUIT)
	{
		if (should_fork(node->right))
			status = forking_node(node->right);
		else
			status = exec_command(node->right);
		if (get_status() == 128 + SIGQUIT)
		{
			if (node->previous && node->previous->type == PIPE)
				node->previous->sigquit = true;
			else
				node->sigquit = true;
		}
	}
	return (get_status());
}
