/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:24:41 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 04:21:26 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

/*
remplace les retours a la ligne (\n)
par "\n" ('\' + 'n')
*/
char	*replace_newline(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (count_char(str, '\n') == 0)
		return (str);
	res = ft_malloc(sizeof(char)
			* (ft_strlen(str) + count_char(str, '\n') + 1));
	if (res == NULL)
		return (error_log("replace_newline: malloc", true), str);
	while (str[++i] != '\0')
	{
		if (str[i] == '\n')
		{
			res[++j] = '\\';
			res[++j] = 'n';
		}
		else
			res[++j] = str[i];
	}
	res[++j] = '\0';
	return (res);
}
