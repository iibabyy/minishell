/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:15:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 00:05:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	new_word_token(t_token **tokens, char *word)
{
	t_token	*new_token;

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

int	metachar_size(char **input, int start)
{
	int			i;

	i = 0;
	while (is_meta_char((*input), start + i) == true
		&& (*input)[start + i] != ' ')
		++i;
	return (i);
}

int	quotes_size(char **input, int start, char eof)
{
	char	*temp;
	int		i;

	i = 0;
	while (1)
	{
		if ((*input)[start + i] == '\0')
		{
			if (eof == '"')
				temp = get_input(&eof, "dquote> ", true);
			else
				temp = get_input(&eof, "quote> ", true);
			*input = ft_re_strjoin(*input, temp);
			if (temp == NULL || *input == NULL)
				return (error_log("quotes_size: get_input() failed", false),
					ft_free(temp), -1);
		}
		if ((*input)[start + i] == eof)
			break ;
		++i;
	}
	return (i);
}

int	parenthesis_size(char *input, int *i)
{
	int	parenthesis;
	int	j;

	parenthesis = 1;
	j = 0;
	while (1)
	{
		if (input[*i] == '(')
			++parenthesis;
		if (input[*i] == ')')
			--parenthesis;
		if (input[*i] == '\0')
		{
			parse_err(TOKEN_ERR, "newline");
			return (-1);
		}
		if (parenthesis == 0 && input[*i] == ')')
			break ;
		++*i;
		++j;
	}
	if (j == 0)
		return (parse_err(TOKEN_ERR, ")"), -1);
	++*i;
	return (j);
}

t_token	*last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}
