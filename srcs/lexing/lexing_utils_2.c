/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:44:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/10 14:27:53 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*replace_wave(char *input)
{
	char	*res;
	char	*home;
	char	**temp;
	int		i;

	home = ft_getenv("HOME");
	if (count_char(input, '~') == 0 || home == NULL)
		return (input);
	temp = ft_split(input, ' ');
	if (temp == NULL || temp[0] == NULL)
		return (input);
	i = -1;
	while (temp[++i] != NULL)
	{
		if (ft_strcmp(temp[i], "~") == 0)
		{
			temp[i] = ft_strdup(home);
			if (temp[i] == NULL)
				return (free_2d_array((void ***)&temp), input);
		}
	}
	res = str_join_2d_and_free(temp, " ");
	if (res == NULL)
		return (input);
	return (res);
}

// static bool	is_expandable(char *str)
// {
// 	char	*wave;

// 	if (ft_strcmp(temp[i], "~") == 0)
// 		return (true);
// 	wave = ft_strchr(str, '~');
// 	if (wave == NULL)
// 		return (false);
// 	while (wave != NULL)
// 	{
		
// 	}
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
