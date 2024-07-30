#include "lexing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

char *type_to_str(int type);
void print_lexing(t_token *tokens);

int main()
{
	char *test = "cat <<<< EOF > cat |>| eco.>ho $PATH ' ghhhhhhhhhhhhh    h'>>";
	printf("%c%s%c:\n", '"', test, '"');
	t_token	*token = input_to_tokens(test);
	print_lexing(token);
	ft_lstclear(&token, ft_free);
	destroy_garbage(0);
	return (0);
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
