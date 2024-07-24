/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:24:44 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

char	*multi_strjoin(int strings_number, char *s1, char *s2, ...)
{
	char	*str;
	va_list	ap;

	if (strings_number < 3)
		return (NULL);
	va_start(ap, s2);
	str = ft_strjoin(s1, s2);
	if (!str)
		return (va_end(ap), NULL);
	strings_number -= 2;
	while (strings_number--)
	{
		str = ft_re_strjoin(str, va_arg(ap, char *));
		if (!str)
			return (va_end(ap), NULL);
	}
	va_end(ap);
	return (str);
}
