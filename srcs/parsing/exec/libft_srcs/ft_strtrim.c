/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:27 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/21 18:29:02 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	verif_set(char letter, const char *set)
{
	int	i;

	i = 0;
	if (set == NULL)
		return (0);
	if (!(letter))
		return (1);
	while (set[i])
	{
		if (letter == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		top;
	size_t	start;
	size_t	end;
	char	*strrim;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	end = ft_strlen(s1) - 1;
	start = 0;
	top = 1;
	while (s1[i] && verif_set(s1[start], set))
		start++;
	while (end >= start && verif_set(s1[end], set))
		end--;
	strrim = ft_substr(s1, start, end - start + 1);
	return (strrim);
}

/*int main(void)
{
	printf("%s" , ft_strtrim("lorem ipsum dolor sit amte", "etl"));
}*/
