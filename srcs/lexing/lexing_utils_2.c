/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:44:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 01:39:47 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*replace_wave(char *input)
{
	char	*res;
	char	*home;
	int		i;
	int		y;

	home = ft_getenv("HOME");
	if (count_char(input, '~') == 0 || home == NULL)
		return (input);
	res = ft_malloc(sizeof(char) * (ft_strlen(input)+ (count_char(input, '~')
			* ft_strlen(home))));
	if (res == NULL)
		return (input);
	i = -1;
	y = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '~')
		{
			ft_memcpy(res + y, home, sizeof(char) * ft_strlen(home));
			y += ft_strlen(home);
		}
		else
			res[y++] = input[i];
	}
	return (res[y] = '\0', res);
}

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
