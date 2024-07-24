/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:30 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;
	char	*retval;

	i = 0;
	j = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (big[i] && i < n)
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && big[i + j] && little[j] && i
				+ j < n)
			{
				if (j + 1 == ft_strlen((char *)little))
					return (retval = (char *)&big[i], retval);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdlib.h>
#include <unistd.h>

static void	ft_prsize_t_result(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void	check_strnstr(char *big, char *little, size_t len)
{
	const char	*str;

	if (!(str = ft_strnstr(big, little, len)))
		ft_prsize_t_result("NULL");
	else
		ft_prsize_t_result(str);
}

size_t	main(size_t argc, const char *argv[])
{
	size_t	arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_strnstr("lorem ipsum dolor sit amet", "lorem", 15);
	else if (arg == 2)
		check_strnstr("lorem ipsum dolor sit amet", "ipsum", 15);
	else if (arg == 3)
		check_strnstr("lorem ipsum dolor sit lorem ipsum dolor", "ipsum", 35);
	else if (arg == 4)
		check_strnstr("lorem ipsum dolor sit amet", "", 10);
	else if (arg == 5)
		check_strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);
	else if (arg == 6)
		check_strnstr("lorem ipsum dolor sit amet", "dol", 30);
	else if (arg == 7)
		check_strnstr("lorem ipsum dolor sit amet", "consectetur", 30);
	else if (arg == 8)
		check_strnstr("lorem ipsum dolor sit amet", "sit", 10);
	else if (arg == 9)
		check_strnstr("lorem ipsum dolor sit amet", "dolor", 15);
	else if (arg == 10)
		check_strnstr("lorem ipsum dolor sit amet", "dolor", 0);
	return (0);
}
*/