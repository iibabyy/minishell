/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:07:45 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:23:35 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	redirections_number(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		if (token->type == REDIRECTION)
			++i;
		token = token->next;
	}
	return (i);
}

int	type_to_oflags(int type)
{
	if (type == OUTPUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == APPEND_OUTPUT)
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (type == INPUT)
		return (O_RDONLY);
	if (type == HERE_DOC)
		return (O_RDWR | O_APPEND);
	return (-1);
}

int	weight_by_type(int type)
{
	if (type == SUB_SHELL)
		return (SUB_SH_WEIGHT);
	else if (type == AND)
		return (AND_WEIGHT);
	else if (type == OR)
		return (OR_WEIGHT);
	else if (type == PIPE)
		return (PIPE_WEIGHT);
	else
		return (-1);
}

int	next_operator_weight(t_parsing *data)
{
	t_token	*operator;
	int		type;

	operator = data->curr_token;
	while (operator != NULL && operator->type != OPERATOR)
	{
		operator = operator->next;
	}
	if (operator == NULL)
		return (0);
	type = token_to_operator_type(operator);
	return (weight_by_type(type));
}

bool	is_whitespace(char c)
{
	if (c == '\t' || c == ' ')
		return (true);
	return (false);
}
