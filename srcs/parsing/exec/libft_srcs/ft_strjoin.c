/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:39 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:41:41 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;

	strjoin = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(strjoin))
		return (NULL);
	ft_strlcpy(strjoin, s1, ft_strlen(s1) + 1);
	ft_strlcat(strjoin, (char *)s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (strjoin);
}
