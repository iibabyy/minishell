/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:15:43 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/07 15:35:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*get_word(char **input, int *i, t_token **tokens);
char	*join_quotes(char **input, char *word, int *i);
char	*join_non_meta_char(char *input, char *word, int *i);

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

	i = 0;
	tokens = NULL;
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			++i;
		if (word_to_token(&input, &i, &tokens) == EXIT_FAILURE)
			return (ft_addhistory(input), NULL);
		while (input[i] == ' ')
			++i;
		if (meta_to_token(&input, &i, &tokens) == EXIT_FAILURE)
			return (ft_addhistory(input), ft_lstclear(&tokens, ft_free), NULL);
	}
	ft_addhistory(input);
	return (tokens);
}

int	word_to_token(char **input, int *i, t_token **tokens)
{
	char	*word;

	word = NULL;
	if (is_parenthesis(*input, *i) == true)
	{
		return(join_parenthesis(*input, i, tokens));
	}
	while (is_meta_char(*input, *i) == false &&
			is_parenthesis(*input, *i) == false && (*input)[*i] != '\0')
	{
		word = join_non_meta_char(*input, word, i);
		if (word == NULL && is_quotes((*input)[*i]) == false)
			return (EXIT_FAILURE);
		word = join_quotes(input, word, i);
		if (word == NULL)
			return (EXIT_FAILURE);
	}
	if (word == NULL)
		return (EXIT_SUCCESS);
	return (new_word_token(tokens, word));
}

// char	*get_word(char **input, int *i)
// {
// 	char	*word;

// 	word = NULL;
// 	while (is_meta_char(*input, *i) == false && (*input)[*i] != '\0')
// 	{
// 		word = join_non_meta_char(*input, word, i);
// 		if (word == NULL)
// 			return (NULL);
// 		word = join_quotes(input, word, i);
// 		if (word == NULL)
// 			return (NULL);
// 	}
// 	return (word);
// }

char	*join_quotes(char **input, char *word, int *i)
{
	char	*temp;
	char	quote;
	int		start;

	if (is_quotes((*input)[*i]) == false)
		return (word);
	quote = (*input)[*i];
	start = ++*i;
	*i += quotes_size(input, start, quote);
	if (*i == -1)
		return (ft_free(word), NULL);
	temp = ft_substr(*input, start, *i - start);
	if (temp == NULL)
		return (ft_free(word), NULL);
	if (quote == '"')
	{
		temp = replace_env_vars(temp);
		if (temp == NULL)
			return (ft_free(word), NULL);
	}
	(*i)++;
	word = ft_re_strjoin(word, temp);
	ft_free(temp);
	return (word);
}

char	*join_non_meta_char(char *input, char *word, int *i)
{
	char	*temp;
	int	start;

	start = *i;
	while (is_meta_char(input, *i) == false && is_quotes(input[*i]) == false
			&& is_parenthesis(input, *i) == false && input[*i] != '\0')
	{
		(*i)++;
	}
	if (*i == start)
		return (word);
	temp = ft_substr(input, start, *i - start);
	if (temp == NULL)
		return (ft_free(word), NULL);
	temp = replace_env_vars(temp);
	if (temp == NULL)
		return (ft_free(word), NULL);
	word = ft_re_strjoin(word, temp);
	ft_free(temp);
	return (word);
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

int	join_parenthesis(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;
	char	*content;
	int		start;
	int		len;

	if (is_parenthesis(input, *i) == false)
		return (EXIT_FAILURE);
	if (input[(*i)++] == ')')
		return (parse_err(TOKEN_ERR, ")"), EXIT_FAILURE);
	start = *i;
	len = parenthesis_size(input, i);
	if (len == -1)
		return (error_log("new_parenthesis: parenthesis_size failed", false),
			EXIT_FAILURE);
	content = ft_substr(input, start, len);
	if (content == NULL)
		return (error_log("new_parenthesis: ft_substr failed", false),
			EXIT_FAILURE);
	new_token = ft_lstnew(content);
	if (new_token == NULL)
		return (error_log("new_parenthesis: ft_substr failed", false),
			EXIT_FAILURE);
	new_token->type = PARENTHESIS;
	ft_lstadd_back(tokens, new_token);
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
