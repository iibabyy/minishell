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
void handle_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}
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

int main()
{
	char *str;
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
			printf("exit\n");
			exit(status);
		}
		if (ft_strcmp(str, "exit") == 0)
		{
			free(str);
			break ;
		}
		if (!is_only_space(str))
		{
			command = parse(str);
			status = exec_command(command, data);
			free(str);
		}
	}
	destroy_garbage(0);
	exit (status);
}

void	print_AST(t_command *command)
{
	int array[1024] = {0};

	command = last_command(command);
	printTree(command, 0, 0, array);
}


void print_command(t_command *command)
{
	int i;

	i = -1;
    if (command->type == COMMAND)
    {
		printf("%s", command->command[++i]);
		while (command->command[++i] != NULL)
		{
			printf(" (\"%s\")", command->command[i]);
		}
		if (command->infile != STDIN_FILENO)
			printf(" | infile: %i", command->infile);
		else
			printf(" | infile: STD");
		if (command->outfile != STDOUT_FILENO)
			printf(" | outfile: %i", command->outfile);
		else
			printf(" | outfile: STD");
	}
	else
		printf ("%s", operator_type_to_str(command->type));
}

void printTree(t_command *command, int depth, int isRight, int *branch) {
    if (depth > 0) {
        for (int i = 0; i < depth - 1; i++) {
            if (branch[i]) printf("│   ");
            else printf("    ");
        }
        printf("%s", isRight ? "└──" : "├──");
    }

    if (command == NULL) {
        printf("NULL\n");
        return;
    }

    print_command(command);
    printf("\n");

    if (command->left != NULL || command->right != NULL) {
        branch[depth] = (command->right != NULL);
        printTree(command->left, depth + 1, command->right == NULL, branch);
        printTree(command->right, depth + 1, 1, branch);
    }
}

char *operator_type_to_str(int type)
{
	if (type == AND)
		return (ft_strdup("AND"));
	if (type == OR)
		return (ft_strdup("OR"));
	if (type == PIPE)
		return (ft_strdup("PIPE"));
	return (NULL);
}

char *type_to_str(int type)
{
	if (type == WORD)
		return (ft_strdup("WORD"));
	if (type == STRING)
		return (ft_strdup("STRING"));
	if (type == OPERATOR)
		return (ft_strdup("OPERATOR"));
	if (type == REDIRECTION)
		return (ft_strdup("REDIRECTION"));
	return (NULL);
}
