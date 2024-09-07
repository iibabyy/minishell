/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:41:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/07 14:16:48 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	init_minishell(char **env)
{
	ft_malloc(0);
	init_history();
	//init_aliases();
	init_error_log();
	init_env(env);
	return (EXIT_SUCCESS);
}

char	*get_line(int last_status)
{
	char	*str;

	str = readline(minishell_prompt());
	if (g_signal != 0)
		return (NULL);
	if (str == NULL)
	{
		destroy_garbage(NULL);
		printf("exit\n");
		exit(last_status);
	}
	if (is_only_space(str) == true)
		return (free(str), NULL);
	if (ft_strcmp(str, "export") == 0)
		return (free(str), export(ft_split(str, ' ')), NULL);
	else if (ft_strcmp(str, "unset") == 0)
		return (free(str), unset(ft_split(str, ' ')), NULL);
	else if (ft_strcmp(str, "env") == 0)
		return (free(str), env(ft_split(str, ' ')), NULL);
	else
		return (str);
}

int	exec(t_command *command)
{
	t_exec_data data;
	int			status;

	if (command == NULL)
		return (0);
	// print_AST(command);
	ft_memset(&data, 0, sizeof(t_exec_data));
	data.pid = ft_calloc (sizeof(int) , 10);
	status = exec_command(command, &data);
	if (status== 128 + SIGSTOP)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
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
