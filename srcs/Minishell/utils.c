/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:41:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/09 01:16:59 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	init_minishell(char **env)
{
	ft_malloc(0);
	init_history();
	init_aliases();
	init_error_log();
	init_env(env);
	return (EXIT_SUCCESS);
}

char	*get_line(void)
{
	char	*str;

	str = readline(minishell_prompt());
	if (g_signal != 0)
		return (NULL);
	if (str == NULL)
	{
		printf("exit\n");
		free_and_exit(get_code(0, GET));
	}
	if (is_only_space(str) == true)
		return (free(str), NULL);
	return (str);
}

int	exec(t_command *command)
{
	int			status;

	if (command == NULL)
		return (EXIT_FAILURE);
	set_parent_exec_signals();
	if (command->type != COMMAND)
		status = exec_command(command);
	else
		status = exec_single(command);
	// if (status == 128 + SIGINT)
	// 	ft_putstr_fd("\n", STDERR_FILENO);
	// if (status == 128 + SIGQUIT)
	// 	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	return (status);
}

bool	is_only_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] != ' ')
			return (false);
	}
	return (true);
}
