/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:09:39 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 12:36:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	next_valid_dollar(char *str, int *i)
{
	char	*dollar;

	dollar = ft_strchr(str + *i, '$');
	while (dollar)
	{
		if (is_in_quotes(str, dollar - str) == SQUOTE)
		{
			dollar = ft_strchr(dollar + 1, '$');
			continue ;
		}
		*i = dollar - str;
		return (*i);
	}
	*i = ft_strlen(str);
	return (*i);
}

int	skip_quotes(char *str, int *i)
{
	int		j;
	char	eof;

	j = *i;
	if (is_quotes(str[j]) == false)
		return (error_log("skip_quotes: not an quote", false), j);
	eof = str[j++];
	while (str[j] != eof && str[j] != '\0')
		++j;
	*i = j;
	return (j);
}

int	skip_parenthesis(char *str, int *i)
{
	if (str[*i] != '(')
		return (error_log("skip_parenthesis: not an parenthesis", false), *i);
	++*i;
	if (parenthesis_size(str, i) == -1)
		return (error_log("skip_parenthesis: parenthesis_size", false), -1);
	return (*i);
}

int	is_in_quotes(char *str, int i)
{
	int		j;
	int		quotes;

	j = -1;
	quotes = 0;
	while (str[++j] != '\0' && j < i)
	{
		if (str[j] == '\'' && quotes != DQUOTE)
		{
			if (quotes == 0)
				quotes = SQUOTE;
			else
				quotes = 0;
		}
		if (str[j] == '"' && quotes != SQUOTE)
		{
			if (quotes == 0)
				quotes = DQUOTE;
			else
				quotes = 0;
		}
	}
	return (quotes);
}

int	is_in_parenthesis(char *str, int i)
{
	int		j;

	j = -1;
	while (str[++j] != '\0' && j < i)
	{
		if (str[j] == '(')
		{
			if (parenthesis_size(str, &j) == -1)
				return (-1);
			if (j - 1 > i)
				return (true);
		}
	}
	return (false);
}
