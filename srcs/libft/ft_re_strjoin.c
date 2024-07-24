/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:20 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 21:02:25 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

static void	ft_free(void **address)
{
	if (*address == NULL)
		return ;
	free(*address);
	*address = NULL;
}

char	*ft_re_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		ft_free((void **)&s1);
		return (NULL);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len + 1);
	ft_free((void **)&s1);
	return (str);
}
