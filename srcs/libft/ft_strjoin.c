/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:20 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*str;

	if (s1 == NULL && s2 != NULL)
	{
		str = ft_strdup(s2);
		return (str);
	}
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (len + 5));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len + 1);
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

static void	check_strjoin(char *s1, char *s2)
{
	char	*strjoin;

	if (!(strjoin = ft_strjoin(s1, s2)))
		ft_print_result("NULL");
	else
		ft_print_result(strjoin);
	if (strjoin == s1 || strjoin == s2)
		ft_print_result("\nA new string was not returned");
	else
		free(strjoin);
}

int	main(int argc, const char *argv[])
{
	char	s1[];
	char	s2[];
	int		arg;

	s1[] = "lorem ipsum";
	s2[] = "dolor sit amet";
	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		check_strjoin(s1, s2);
	}
	else if (arg == 2)
	{
		s1[0] = '\0';
		check_strjoin(s1, s2);
	}
	else if (arg == 3)
	{
		s2[0] = '\0';
		check_strjoin(s1, s2);
	}
	else if (arg == 4)
	{
		s1[0] = '\0';
		s2[0] = '\0';
		check_strjoin(s1, s2);
	}
	return (0);
}
*/