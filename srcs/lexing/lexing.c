#include "lexing.h"

/*
Transform an input string in tokens
Return an t_token chained list with their content and types
Return NULL if an error occurs
Return NULL and print an error message if there is opened quotes
*/
t_token	*input_to_tokens(char **input)
{
	t_token	*tokens;
	int		i;
	int		token_start;

	i = 0;
	tokens = NULL;
	while ((*input)[i] != '\0')
	{
		while ((*input)[i] == ' ')
			++i;
		token_start = i;
		while (is_meta_char(*input, i) == false && (*input)[i] != '\0') //TODO: the while stop if an metachar appears even in a string ("cat 'ab|c'"")
			++i;
		if (word_to_token(input, token_start, &i, &tokens) == EXIT_FAILURE)
			return (ft_lstclear(&tokens, ft_free), NULL);
		while ((*input)[i] == ' ')
			++i;
		if (meta_to_token(input, &i, &tokens) == EXIT_FAILURE)
			return (ft_lstclear(&tokens, ft_free), NULL);
	}
	return (tokens);
}


int	word_to_token(char **input, int i, int *end, t_token **tokens)
{
	t_token	*new_token;
	char	*word;
	int 	len;

	if (*end - i == 0 || (*input)[i] == '\0')
		return (EXIT_SUCCESS);
	if (is_quotes((*input)[i]) == true)
	{
		len = quotes_size(input, i + 1, (*input)[i]);
		*end = ++i + len + 1;
	}
	else
		len = *end - i;
	word = ft_substr(*input, i, len);
	if (word == NULL)
		return (EXIT_FAILURE);
	new_token = ft_lstnew(word);
	if (new_token == NULL)
		return (ft_free(word), EXIT_FAILURE);
	new_token->type = WORD;
	if (*tokens == NULL)
		*tokens = new_token;
	else
		ft_lstadd_back(tokens, new_token);
	return (EXIT_SUCCESS);
}

int	meta_to_token(char **input, int *index, t_token **tokens)
{
	t_token	*new_token;

	if (is_meta_char(*input, *index) == false)
		return (EXIT_SUCCESS);
	new_token = init_token(input, *index);
	if (new_token == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(tokens, new_token);
	*index += metachar_size(input, *index);
	return (EXIT_SUCCESS);
}


int	metachar_size(char **input, int start)
{
	int			i;
	
	i = 0;
	while (is_meta_char((*input), start + i) == true && (*input)[start + i] != ' ')
		++i;
	return (i);
}
