#include "lexing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

char *type_to_str(int type);
void print_lexing(t_token *tokens);
void	print_command(t_command *command);
char *operator_type_to_str(int type);

void print_command(t_command *command) {
    if (command->type == COMMAND)
        printf("%s", command->command[0]);
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

int main()
{
	char *str = "cat | ls && ls || ls";
	str = replace_env_vars(str);
	t_token *token = input_to_tokens(str);
	t_command *command = token_to_ast(token);
	int array[1024] = {0};
	printTree(command, 0, 0, array);
	destroy_garbage(0);
	return (0);
}

char *operator_type_to_str(int type)
{
	if (type == AND)
		return (ft_strdup("AND"));
	if (type == OR)
		return (ft_strdup("OR"));
	if (type == PIPE)
		return (ft_strdup("PIPE"));
	return (ft_strdup("?"));
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

void print_lexing(t_token *token)
{
	char *type;

	if (token == NULL)
		return ((void)printf("NULL token\n"));
	while (token != NULL)
	{
		type = type_to_str(token->type);
		printf("'%s' (%s)", token->content, type);
		if (token->next != NULL)
			printf(" ");
		ft_free(type);
		token = token->next;
	}
	printf("\n");
	
}