/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_remove_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:17:02 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:42:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*Return an allocated copy of the str 
without the char c in parameter
Return NULL if an error occurs*/
char	*ft_re_remove_char(char *str, char c)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(str) - count_char(str, c);
	if (size == 0 || c == '\0')
		return (ft_free(str), NULL);
	new = ft_malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (ft_free(str), malloc_failed("ft_re_remove_char"), NULL);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != c)
			new[++j] = str[i];
	}
	new[j] = '\0';
	return (ft_free(str), new);
}
