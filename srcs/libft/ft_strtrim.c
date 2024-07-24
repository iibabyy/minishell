/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:33:17 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	end;
	size_t	start;

	if (!s1 || !set)
		return (0);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end && ft_strchr(set, s1[end]))
		end--;
	str = ft_substr(s1, start, (end - start + 1));
	return (str);
}

/*
#include <unistd.h>

static void	ft_print_result(char const *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void	check_strtrim(char *s1, char *set)
{
	char	*strtrim;

	if (!(strtrim = ft_strtrim(s1, set)))
		ft_print_result("NULL");
	else
		ft_print_result(strtrim);
	if (strtrim == s1)
		ft_print_result("\nA new string was not returned");
	else
		free(strtrim);
}

int	main(int argc, const char *argv[])
{
	int		arg;
	char	s1[];
	char	s1[];
	char	s1[];
	char	s1[];
	char	s1[];

		s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
		s1[] = "lorem ipsum dolor sit amet \n \t ";
		s1[] = " \n \t lorem ipsum dolor sit amet";
		s1[] = "  \n  \t  lorem \n ipsum \t dolor \n sit \t amet  \t \n ";
		s1[] = "          ";
	char	set [] = "\t \n";
	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		check_strtrim(s1, set);
	}
	else if (arg == 2)
	{
		check_strtrim(s1, set);
	}
	else if (arg == 3)
	{
		check_strtrim(s1, set);
	}
	else if (arg == 4)
	{
		check_strtrim(s1, set);
	}
	else if (arg == 5)
	{
		check_strtrim(s1, set);
	}
	return (0);
}
*/