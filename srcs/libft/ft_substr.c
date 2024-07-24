/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:09:08 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int			i;
	int			size;
	const char	*str;

	i = 0;
	if (len >= ft_strlen(s + start))
		str = malloc(sizeof(char) * ft_strlen(s + start));
	else
		str = malloc(sizeof(char) * len);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
}
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (len > ft_strlen(s))
		size = ft_strlen(s);
	else
		size = len;
	str = malloc(sizeof(char) * (size + 1));
	if (!s || !str)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < size)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

/*#include <unistd.h>

static void	ft_print_result(char const *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void	check_substr(char *str, int start, int len)
{
	char	*substr;

	if (!(substr = ft_substr(str, start, len)))
		ft_print_result("NULL");
	else
		ft_print_result(substr);
	if (str == substr)
		ft_print_result("\nA new string was not returned");
	else
		free(substr);
}

int	main(int argc, const char *argv[])
{
	char	*str;
	int		arg;

	str = "lorem ipsum dolor sit amet";
	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_substr(str, 0, 10);
	else if (arg == 2)
		check_substr(str, 7, 10);
	else if (arg == 3)
		check_substr(str, 7, 0);
	else if (arg == 4)
		check_substr(str, 0, 0);
	return (0);
}
*/