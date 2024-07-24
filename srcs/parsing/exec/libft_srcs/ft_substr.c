/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/21 22:47:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sub_len;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = malloc(sizeof(char));
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	substr = malloc(sizeof(char) * (sub_len + 1));
	if (!(substr))
		return (NULL);
	ft_strlcpy(substr, s + start, sub_len + 1);
	return (substr);
}
