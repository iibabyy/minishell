/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:53:38 by mdembele          #+#    #+#             */
/*   Updated: 2024/06/23 17:25:59 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_re_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;

	strjoin = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(strjoin))
		return (ft_free((void **)&s1), NULL);
	ft_strlcpy(strjoin, s1, ft_strlen(s1) + 1);
	ft_strlcat(strjoin, (char *)s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (ft_free((void **)&s1), strjoin);
}
