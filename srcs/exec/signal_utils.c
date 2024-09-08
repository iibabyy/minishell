/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:48:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/09 00:52:45 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_code(int error_code, bool setter)
{
	static int	code = 0;

	if (setter == false)
		return (code);
	code = error_code;
	return (code);
}

void	set_exit_code(int status)
{
	if (WIFSIGNALED(status))
		get_code(128 + WTERMSIG(status), SET);
	else if (WIFSTOPPED(status))
		get_code(128 + WSTOPSIG(status), SET);
	else if (WIFEXITED(status))
		get_code(WEXITSTATUS(status), SET);
}

char	*check_heredoc_sig(char *input, char *eof)
{
	if (g_signal != 0)
	{
		// printf("ok\n");
		return (ft_free(input), NULL);
	}
	else
	{	ft_putstr_fd
			("minishell: warning: here-document delimited by end-of-file (wanted `",
				STDERR_FILENO);
		ft_putstr_fd(eof, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
	return (input);
}
