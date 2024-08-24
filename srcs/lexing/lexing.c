/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:15:43 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/20 22:55:46 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (word_to_token(&input, token_start, &i, &tokens) == EXIT_FAILURE)
			return (add_history(input), ft_lstclear(&tokens, ft_free), NULL);
		while (input[i] == ' ')
			++i;
		if (meta_to_token(&input, &i, &tokens) == EXIT_FAILURE)
			return (add_history(input), ft_lstclear(&tokens, ft_free), NULL);
	}
	add_history(input);
	if (replace_tokens_env_vars(tokens) == EXIT_FAILURE)
		return (ft_lstclear(&tokens, ft_free), NULL);
	return (tokens);
}

int	word_to_token(char **input, int i, int *end, t_token **tokens)
{
	char	*word;
	int		len;

	if (*end - i == 0 || (*input)[i] == '\0')
		return (EXIT_SUCCESS);
	if ((*input)[i] == ')' || (*input)[i] == '(')
		return (new_parenthesis(input, i, end, tokens));
	if (is_quotes((*input)[i]) == true)
	{
		len = quotes_size(input, i + 1, (*input)[i]);
		if (len == -1)
			return (EXIT_FAILURE);
		*end = ++i + len + 1;
	}
	else
		len = *end - i;
	word = ft_substr(*input, i, len);
	if (word == NULL)
		return (EXIT_FAILURE);
	if (new_word_token(tokens, word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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

int	new_parenthesis(char **input, int start, int *end, t_token **token)
{
	char	*content;
	t_token	*new_token;
	int		len;

	if ((*input)[start++] == ')')
		return (parse_err(TOKEN_ERR, ")"), EXIT_FAILURE);
	len = parenthesis_size(input, start);
	if (len == -1)
		return (error_log("new_parenthesis: quotes_size failed", false),
			EXIT_FAILURE);
	content = ft_substr(*input, start, len);
	if (content == NULL)
		return (error_log("new_parenthesis: ft_substr failed", false),
			EXIT_FAILURE);
	new_token = ft_lstnew(content);
	if (new_token == NULL)
		return (error_log("new_parenthesis: ft_substr failed", false),
			EXIT_FAILURE);
	new_token->type = PARENTHESIS;
	ft_lstadd_back(token, new_token);
	*end = start + len + 1;
	return (EXIT_SUCCESS);
}

t_token	*init_token(char **input, int start)
{
	t_token	*new_token;
	char	*content;
	int		len;

	new_token = ft_calloc(1, sizeof(t_token) * 1);
	if (new_token == NULL)
		return (NULL);
	new_token->next = NULL;
	new_token->type = char_type(*input, start);
	len = metachar_size(input, start);
	if (len == -1 || new_token->type == -1)
		return (ft_free(new_token), NULL);
	content = ft_substr(*input, start, len);
	if (content == NULL)
		return (ft_free(new_token), NULL);
	new_token->content = content;
	return (new_token);
}
