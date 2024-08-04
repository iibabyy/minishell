#include "../includes/minishell.h"

void	print_AST(t_command *command);

int main(void)
{
	char *str;
	t_command *command;

	init_aliases(void);
	init_error_log(void);
	while (1)
	{
		str = readline("\033[0;36mminishell \033[0;33m✗\033[0m ");
		if (ft_strcmp(str, "exit") == 0)
		{
			free(str);
			break ;
		}
		add_history(str);
		command = parse(str);
		free(str);
		if (command == NULL)
			continue ;
		print_AST(command);
		free(str);
	}
	destroy_garbage(0);
	return (0);
}

int	init_minishell(void)
{

}
