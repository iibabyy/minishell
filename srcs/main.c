#include "../includes/minishell.h"

/*		UTILS	*/

char *type_to_str(int type);
void	print_command(t_command *command);
char *operator_type_to_str(int type);
void printTree(t_command *command, int depth, int isRight, int *branch);
t_command	*last_command(t_command *current);
void	print_AST(t_command *command);
void    exec_command(t_command *);

/*				*/

int main()
{
	char *str;
	t_command *command;

	while (1)
	{
		str = readline("\033[0;36mminishell \033[0;33m✗\033[0m ");
		if (ft_strcmp(str, "exit") == 0)
		{
			free(str);
			break ;
		}
		command = parse(str);
		exec_command(command);
		print_AST(command);
		free(str);
	}
	destroy_garbage(0);
	return (0);
}

void	print_AST(t_command *command)
{
	int array[1024] = {0};

	command = last_command(command);
	printTree(command, 0, 0, array);
}


void print_command(t_command *command)
{
    if (command->type == COMMAND)
    {
		printf("%s ({%s})", command->command[0], str_join_2d(&command->command[1], ", "));
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
