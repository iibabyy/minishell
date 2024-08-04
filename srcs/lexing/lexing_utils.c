/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:15:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/04 22:15:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

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
			temp = get_input(&eof, QUOTES_PROMPT, true);
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

int	parenthesis_size(char **input, int start)
{
	int		parenthesis;
	int		i;

	i = 0;
	parenthesis = 1;
	while (1)
	{
		if ((*input)[start + i] == '(')
			++parenthesis;
		if ((*input)[start + i] == ')')
			--parenthesis;
		if ((*input)[start + i] == '\0')
		{
			ft_putstr_fd("syntaxe error near unexpected token: `(",
				STDERR_FILENO);
			ft_putstr_fd(&(*input)[start], STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (-1);
		}
		if (parenthesis == 0 && (*input)[start + i] == ')')
			break ;
		++i;
	}
	return (i);
}
