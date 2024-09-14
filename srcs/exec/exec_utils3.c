/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:55:21 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 04:59:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../built_in/built_in.h"
#include "exec.h"
#include <unistd.h>

bool	test_cd(t_command *command)
{
	struct stat	buf;

	if (command->previous != NULL || command->type != COMMAND)
		return (false);
	if (command->redirections != NULL)
		return (false);
	if (command->command == NULL || command->command[0] == NULL
		|| command->command[1] != NULL)
		return (false);
	if (access(command->command[0], X_OK) != 0)
		return (false);
	if (stat(command->command[0], &buf) == -1)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

int	exec_cd(char *str)
{
	char	**cd_args;

	cd_args = ft_malloc(sizeof(char *) * 3);
	cd_args[0] = ft_strdup("cd");
	cd_args[1] = ft_strdup(str);
	cd_args[2] = NULL;
	return (cd(cd_args));
}

int	exec_sub_shell(t_command *node)
{
	t_command	*command;

	set_subshell_signals();
	if (open_redirections(node) == EXIT_FAILURE)
		free_and_exit(EXIT_FAILURE);
	command = parse_subshell(node->command[0]);
	if (command == NULL)
		free_and_exit(EXIT_FAILURE);
	command->is_child = true;
	free_and_exit(exec(command));
	return (get_status());
}

int	exec_builtin(t_command *node)
{
	char	**args;
	int		status;

	args = node->command;
	if (ft_strcmp("echo", args[0]) == 0)
		status = echo_minishell(args);
	if (ft_strcmp("unset", args[0]) == 0)
		status = unset(args);
	if (ft_strcmp("cd", args[0]) == 0)
		status = cd(args);
	if (ft_strcmp("pwd", args[0]) == 0)
		status = pwd(args);
	if (ft_strcmp("export", args[0]) == 0)
		status = export(args);
	if (ft_strcmp("env", args[0]) == 0)
		status = env(args);
	ft_close(&node->outfile);
	ft_close(&node->infile);
	if (ft_strcmp("exit", args[0]) == 0)
	{
		if (node->is_child == false)
			ft_putendl_fd("exit", STDERR_FILENO);
		status = ft_exit(args);
	}
	return (last_status_code(status, SET), status);
}

int	forking_node(t_command *node)
{
	int	pid;

	pid = ft_fork(node);
	if (pid == 0)
	{
		exec_command(node);
		free_and_exit(get_status());
	}
	ft_waitpid(pid, node);
	return (get_status());
}
