#include "../includes/minishell.h"

/*		UTILS	*/

char *type_to_str(int type);
void	print_command(t_command *command);
char *operator_type_to_str(int type);
void printTree(t_command *command, int depth, int isRight, int *branch);
t_command	*last_command(t_command *current);
void	print_AST(t_command *command);

/*		Test lexing		*/
// int main()
// {
// 	while (1)
// 	{
// 		char *test = readline("\033[0;36mminishell \033[0;33m✗\033[0m ");
// 		t_token	*tokens = parse(test);
// 		if (tokens == NULL)
// 			continue ;
// 		while (tokens != NULL)
// 		{
// 			printf("(%s:)\"%s\" ", type_to_str(tokens->type), tokens->content);
// 			tokens = tokens->next;
// 		}
// 		printf("\n");
// 	}
// 	return 0;
// }

/*		Test parsing	*/

int main()
{
	char *str;
	t_command *command;

	init_aliases();
	init_error_log();
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

void	print_AST(t_command *command)
{
	int array[1024] = {0};

	command = last_command(command);
	printTree(command, 0, 0, array);
}


void print_command(t_command *command)
{
	int 	i;
	char	*infile = "STDIN";
	char	*outfile = "STDOUT";

	i = -1;
    if (command->type == COMMAND || command->type == SUB_SHELL)
    {
		if (command->type == SUB_SHELL)
			printf("(\"%s\")", command->command[++i]);
		else
			printf("%s", command->command[++i]);
		while (command->command[++i] != NULL)
		{
			printf(" (\"%s\")", command->command[i]);
		}
		if (command->redirections != NULL)
		{
			while (command->redirections != NULL)
			{
				if (command->redirections->type == OUTPUT || command->redirections->type == APPEND_OUTPUT)
					outfile = command->redirections->file->content;
				else if (command->redirections->type == INPUT)
					infile = command->redirections->file->content;
				else if (command->redirections->type == HERE_DOC)
					infile = "HERE_DOC";
				command->redirections = command->redirections->next;
			}
		}
		printf(" | infile: %s | outfile: %s", infile, outfile);
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
	if (type == PARENTHESIS)
		return (ft_strdup("PARENTHESIS"));
	return (NULL);
}
