/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:05 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	int					i;
	unsigned const char	*s1;
	unsigned const char	*s2;

	i = 0;
	s1 = str1;
	s2 = str2;
	while (*(s1 + i) == *(s2 + i) && i < (int)n)
		i++;
	if (i >= (int)n)
		return (0);
	return (*(s1 + i) - *(s2 + i));
}

/*
#include "../../includes/libft.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	ft_print_result(int n)
{
	if (n > 0)
		write(1, "1", 1);
	else if (n < 0)
		write(1, "-1", 2);
	else
		write(1, "0", 1);
}

int	main(int argc, const char *argv[])
{
	int	arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		ft_print_result(ft_memcmp("salut", "salut", 5));
	else if (arg == 2)
		ft_print_result(ft_memcmp("t\200", "t\0", 2));
	else if (arg == 3)
		ft_print_result(ft_memcmp("testss", "test", 5));
	else if (arg == 4)
		ft_print_result(ft_memcmp("test", "tEst", 4));
	else if (arg == 5)
		ft_print_result(ft_memcmp("", "test", 4));
	else if (arg == 6)
		ft_print_result(ft_memcmp("test", "", 4));
	else if (arg == 7)
		ft_print_result(ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	else if (arg == 8)
		ft_print_result(ft_memcmp("abcdefgh", "abcdwxyz", 6));
	else if (arg == 9)
		ft_print_result(ft_memcmp("zyxbcdefgh", "abcdefgxyz", 0));
	return (0);
}
*/