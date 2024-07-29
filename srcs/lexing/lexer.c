#include "lexing_utils.h"

t_token	*input_to_tokens(char *input)
{
	t_token	*tokens;
	int		i;
	int		token_start;

	i = -1;
	while (input[++i] != '\0')
	{
		token_start = i;
		while (is_meta_char(input, i) == false && input[i] != '\0')
			++i;
		if (word_to_token(input, token_start, i, &tokens) == EXIT_FAILURE)
			return (ft_lstclear(&tokens, ft_free), NULL);
		if (is_meta_char(input, i) == true)
		{
			if (meta_to_token(input, &i, &tokens) == EXIT_FAILURE)
				return (ft_lstclear(&tokens, ft_free), NULL);
		}
		else if (input[i] == '\0')
			break ;
	}
	return (tokens);
}

int	word_to_token(char *input, int start, int end, t_token **tokens)
{
	t_token	*new_token;
	char	*word;
	int		size;

	word = ft_substr(input, start, index - start);
	if (word == NULL)
		return (EXIT_FAILURE);
	new_token = ft_lstnew(word);
	if (new_token == NULL)
		return (ft_free(word), EXIT_FAILURE);
	new_token->type = WORD
	ft_lstadd_back(tokens, new_token);
}

int	meta_to_token(char *input, int *index, t_token **tokens)
{
	t_token	*new_token;
	char	*content;

	if (is_quotes(input[*index]) == true)
	{
		content = ft_substr(input, index + 1, metachar_size(input, index));
		new_token = ft_lstnew(content);
		if (new_token == NULL || content == NULL)
			return (ft_free(content), ft_free(new_token), EXIT_FAILURE);
		new_token->type = STRING;
		*index += metachar_size(input, index) + 1;
		return (ft_lstadd_back(tokens, new_token), EXIT_FAILURE);
	}
	content = ft_substr(input, index + 1, metachar_size(input, index));
	new_token = ft_lstnew(content);
	if (new_token == NULL || content == NULL)
		return (ft_free(content), ft_free(new_token), EXIT_FAILURE);
	if (is_operator(input, *index) == true)
		new_token->type = OPERATOR;
	else if (is_redirection(input, *index) == true)
		new_token->type = REDIRECTION;
	ft_lstadd_back(tokens, new_token);
	return (EXIT_SUCCESS);
}



































/*
#include "lexing_utils.h"

t_token	*input_to_tokens(char *input)
{
	t_token	*tokens;
	int		i;
	int		token_start;

	i = 0;
	token_start = 0;
	while (input[i] != '\0')
	{
		if (word_to_token(input, &token_start, &i, &tokens) == EXIT_FAILURE)
			return (ft_lstclear(&tokens, ft_free));
		if (is_meta_char(input[i]) == true)
		{
			if (new_token(input, &i) == EXIT_FAILURE)
				return (ft_lstclear(&tokens, ft_free));
		}
		else if (input[i] == '\0')
			break ;
	}
}

int	word_to_token(char *input, int *start, int *index, t_token **tokens)
{
	t_token	*new_token;
	char	*word;
	int		size;

	size = 0;
	while (is_meta_char(input[*i]) == false && input[*i] != '\0')
		(++size, ++(*i));
	word = ft_substr(input, *start, size);
	if (word == NULL)
		return (NULL);
	*start = *i;
	new_token = ft_lstnew(word);
	if (new_token == NULL)
		return (ft_free(word), NULL);
	ft_lstadd_back(tokens, new_token);
}

int	new_token(char *input, int *index)
{
	if ()
}
*/