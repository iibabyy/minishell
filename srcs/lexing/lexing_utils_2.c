/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:44:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/04 19:15:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"



// char	*quote_prompt(char quote)
// {
// 	if (quote == '"')
// 		return (ft_strdup("dquote> ")); 
// 	else if (quote == '\'')
// 		return (ft_srd)
// }

int	char_type(char *str, int index)
{
	char	c;

	c = str[index];
	if (is_quotes(c) == true)
		return (WORD);
	if (is_redirection(c) == true)
		return (REDIRECTION);
	if (ft_strchr("|()", c) != NULL)
		return (OPERATOR);
	if (c == '&' && str[index + 1] == '&')
		return (OPERATOR);
	error_log("unknow token\n", false);
	return (-1);
}
