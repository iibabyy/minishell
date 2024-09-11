/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:09:39 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/11 22:11:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	next_valid_dollar(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != '$')
	{
		if (is_parenthesis(str, *i) == true)
		{
			if (skip_parenthesis(str, i) == -1)
				return (-1);
		}
		else if (str[*i] == '\'')
			skip_quotes(str, i);
		else
			++*i;
	}
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
	if (parenthesis_size(str, i) == -1)
		return (error_log("skip_parenthesis: not an parenthesis", false), -1);
	return (*i);
}


