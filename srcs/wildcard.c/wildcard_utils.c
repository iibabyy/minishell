/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 01:12:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/11 01:16:58 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

bool	need_wildcard_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		while (is_quotes(str[i]) == false && is_parenthesis(str, i) && str[i] != '$')
	}
}
