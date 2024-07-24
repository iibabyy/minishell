/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:40:10 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 21:52:06 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size;

	ft_strlen(big);
	size = ft_strlen(little);
	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i + size <= len && big[i])
	{
		if (ft_strncmp(big + i, little, size) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
	KO  25:          5  check(ft_strnstr(empty, "", -1) == empty); showLeaks();
KO  26:          6  check(ft_strnstr(empty, "", 0) == empty); showLeaks();
*/
