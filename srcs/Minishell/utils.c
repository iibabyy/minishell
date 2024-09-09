/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:41:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/10 00:36:44 by ibaby            ###   ########.fr       */
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
		free_and_exit(get_status());
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
	if (command->type != COMMAND && command->type != SUB_SHELL)
		status = exec_command(command);
	else
		status = exec_single(command);
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

t_command	*parse_subshell(char *input)
{
	t_parsing	data;

	if (input == NULL)
		return (NULL);
	ft_memset(&data, 0, sizeof(t_data));
	data.error = false;
	// input = replace_env_vars(input);
	data.token = input_to_tokens_subshell(input);
	if (data.token == NULL)
		return (destroy_parsing(&data), NULL);
	data.curr_token = data.token;
	data.command = token_to_ast(&data, -2);
	if (data.command == NULL)
		return (destroy_parsing(&data), NULL);
	if (replace_aliases(last_command(data.command)) == EXIT_FAILURE)
		return (destroy_parsing(&data), NULL);
	return (last_command(data.command));
}

t_token	*input_to_tokens_subshell(char *input)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			++i;
		if (word_to_token(&input, &i, &tokens) == EXIT_FAILURE)
			return (ft_addhistory(input), NULL);
		while (input[i] == ' ')
			++i;
		if (meta_to_token(&input, &i, &tokens) == EXIT_FAILURE)
			return (ft_addhistory(input), ft_lstclear(&tokens, ft_free), NULL);
	}
	ft_addhistory(input);
	return (tokens);
}
