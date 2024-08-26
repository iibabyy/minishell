/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:42:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/26 16:21:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec/exec.h"
/*		UTILS	*/

char		*type_to_str(int type);
void		print_command(t_command *command);
char 		*operator_type_to_str(int type);
void 		printTree(t_command *command, int depth, int isRight, int *branch);
t_command	*last_command(t_command *current);
void		print_AST(t_command *command);

/*				*/

bool	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			++i;
		else
			return (false);
	}
	return (true);
}

// TODO: check all whitespaces, not only spaces

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_minishell(envp);
	char *str;
	char **arg;
	t_command *command;
	t_exec_data *data;
	int status;

	status = 0;
    data = ft_calloc(sizeof(t_exec_data), 1);
	data->pid = ft_calloc (sizeof(int) , 10);
	while (1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		if ((str = readline("\033[0;36mminishell \033[0;33m✗\033[0m ")) == NULL)
		{
			destroy_garbage(NULL);
			printf("exit\n");
			exit(status);
		}
		str = replace_env_vars(str);
		add_history(str);
		arg = ft_split(str, ' ');
		if (arg[0] == NULL)
			continue ;
		printf("%s:\n\n", str);
		if (ft_strcmp(arg[0], "export") == 0)
			export(arg);
		else if (ft_strcmp(arg[0], "unset") == 0)
			unset(arg);
		else if (ft_strcmp(arg[0], "alias") == 0)
			alias(arg);
		else if (ft_strcmp(arg[0], "env") == 0)
			env(arg);
		else if (ft_strcmp(arg[0], "exit") == 0)
		{
			free(str);
			destroy_garbage(NULL);
			exit(EXIT_SUCCESS);
		}
		else
		{
			command = parse(str);
			if (command != NULL)
			{	
    			printf("%p\n", command->redirections);
				// print_AST(command);
				exec_command(command, data);
			}
		}
		free(str);
		free_2d_array((void ***)&arg);
	}
	return (0);
}



int	init_minishell(char **env)
{
	ft_malloc(0);
	init_aliases();
	init_error_log();
	init_env(env);
	return (EXIT_SUCCESS);
}
