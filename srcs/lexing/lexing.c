#include "lexing.h"

/*
Transform an input string in tokens
Return an t_token chained list with their content and types
Return NULL if an error occurs
Return NULL and print an error message if there is opened quotes
*/
t_token	*input_to_tokens(char *input)
{
	t_token	*tokens;
	int		i;
	int		token_start;

	i = 0;
	tokens = NULL;
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			++i;
		token_start = i;
		while (is_meta_char(input, i) == false && input[i] != '\0')
			++i;
		if (word_to_token(input, token_start, i, &tokens) == EXIT_FAILURE)
			return (ft_lstclear(&tokens, ft_free), NULL);
		while (input[i] == ' ')
			++i;
		if (is_meta_char(input, i) == true && input[i] != '\0')
		{
			if (meta_to_token(input, i, &tokens) == EXIT_FAILURE)
				return (ft_lstclear(&tokens, ft_free), NULL);
			i += metachar_size(input, i);
		}
	}
	return (tokens);
}

int	word_to_token(char *input, int start, int end, t_token **tokens)
{
	t_token	*new_token;
	char	*word;

	if (end - start == 0 || input[start] == '\0')
		return (EXIT_SUCCESS);
	word = ft_substr(input, start, end - start);
	if (word == NULL)
		return (EXIT_FAILURE);
	new_token = ft_lstnew(word);
	if (new_token == NULL)
		return (ft_free(word), EXIT_FAILURE);
	new_token->type = WORD;
	ft_lstadd_back(tokens, new_token);
	return (EXIT_SUCCESS);
}

int	meta_to_token(char *input, int index, t_token **tokens)
{
	t_token	*new_token;

	new_token = init_token(input, index);
	ft_lstadd_back(tokens, new_token);
	return (EXIT_SUCCESS);
}