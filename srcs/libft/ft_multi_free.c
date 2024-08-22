/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:35:51 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/15 20:44:33 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

void	ft_multi_free(int pointers_num, void *pointer1, void *pointer2, ...)
{
	va_list			ap;
	unsigned char	*pointer;

	va_start(ap, pointer2);
	ft_free(pointer1);
	ft_free(pointer2);
	pointers_num -= 2;
	while (pointers_num-- > 0)
	{
		pointer = va_arg(ap, unsigned char *);
		ft_free(pointer);
	}
}
