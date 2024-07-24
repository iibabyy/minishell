/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:49 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/21 19:22:47 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = ft_strlen(s);
	if (uc == '\0')
		return ((char *)s + i);
	while (i > 0)
	{
		if (s[i - 1] == uc)
			return ((char *)(s + i - 1));
		i--;
	}
	return (NULL);
}
