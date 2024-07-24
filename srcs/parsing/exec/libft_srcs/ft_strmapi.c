/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:40:43 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/20 21:56:34 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strmapi(char const *s, char (*fonction)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (!(s))
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(result))
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = fonction(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
