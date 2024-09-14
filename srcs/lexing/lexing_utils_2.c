/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:44:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:34:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static bool	is_expandable(char *str);
static char	*expand_wave(char *str);

char	*replace_wave(char *input)
{
	char	*res;
	char	**temp;
	int		i;

	if (input == NULL || count_char(input, '~') == 0)
		return (input);
	temp = ft_split(input, ' ');
	if (temp == NULL || temp[0] == NULL)
		return (input);
	i = -1;
	while (temp[++i] != NULL)
	{
		if (is_expandable(temp[i]) == true)
		{
			temp[i] = expand_wave(temp[i]);
			if (temp[i] == NULL)
				return (free_2d_array((void ***)&temp), input);
		}
	}
	res = str_join_2d_and_free(temp, " ");
	if (res == NULL)
		return (input);
	return (res);
}

static char	*expand_wave(char *str)
{
	char	*last;
	char	**temp;
	char	*res;

	last = "";
	if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] == '/')
		last = "/";
	temp = ft_split(str, '/');
	if (temp == NULL)
		return (NULL);
	if (temp[0][0] != '~')
		return (free_2d_array((void ***)&temp), str);
	temp[0] = ft_strdup(ft_getenv("HOME"));
	if (temp[0] == NULL)
		temp[0] = ft_strdup(getenv("HOME"));
	if (temp[0] == NULL)
		return (str);
	res = str_join_2d_and_free(temp, "/");
	if (res == NULL)
		return (str);
	res = ft_re_strjoin(res, last);
	if (res == NULL)
		return (str);
	return (res);
}

static bool	is_expandable(char *str)
{
	if (str[0] != '~')
		return (false);
	if (str[0] == '~' && (str[1] == '/' || str[1] == '\0'))
		return (true);
	return (false);
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
