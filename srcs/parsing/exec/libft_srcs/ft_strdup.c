/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:10 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/20 18:38:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	size;

	size = ft_strlen(s) + 1;
	tab = malloc(sizeof(char) * size);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, size);
	return (tab);
}
