/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:26:41 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:34:59 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	tab_to_spaces(char *input)
{
	int		i;

	if (input == NULL)
		return ;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\t')
			input[i] = ' ';
	}
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

int	quotes_or_parenthesis_2d(char **str, char *is_in, int index)
{
	int	quotes;
	int	i;
	int	j;

	i = -1;
	j = -1;
	quotes = 0;
	while (str[++i])
	{
		if (++j == index && str[i] == is_in)
			return (quotes);
		if (str[i][j] == '"' && quotes == DQUOTE)
			quotes = 0;
		else if (str[i][j] == '"' && quotes == 0)
			quotes = DQUOTE;
		if (str[i][j] == '"' && quotes == SQUOTE)
			quotes = 0;
		else if (str[i][j] == '"' && quotes == 0)
			quotes = SQUOTE;
		if (str[i][j] == '(' && quotes == 0)
			quotes = PARENTHESIS;
		else if (str[i][j] == ')' && quotes == PARENTHESIS)
			quotes = 0;
	}
	return (0);
}
