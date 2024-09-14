/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:48:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 19:57:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	last_status_code(int status, bool setter)
{
	static int	code = 0;

	if (setter == false)
		return (code);
	code = status;
	return (code);
}

int	get_status(void)
{
	return (last_status_code(0, GET));
}

void	set_status(int status)
{
	if (WIFSIGNALED(status))
		last_status_code(128 + WTERMSIG(status), SET);
	else if (WIFSTOPPED(status))
		last_status_code(128 + WSTOPSIG(status), SET);
	else if (WIFEXITED(status))
		last_status_code(WEXITSTATUS(status), SET);
}

char	*check_heredoc_sig(char *input, char *eof)
{
	if (g_signal != 0)
		return (ft_free(input), NULL);
	else
	{
		ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(eof, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
	if (input == NULL)
		input = ft_strdup("");
	return (input);
}
