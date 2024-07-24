/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:35:51 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 21:01:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

static void	ft_free(void **address)
{
	if (*address == NULL)
		return ;
	free(*address);
	*address = NULL;
}

void	ft_multi_free(int pointers_num, void **pointer1, void **pointer2, ...)
{
	va_list			ap;
	unsigned char	**pointer;

	va_start(ap, pointer2);
	ft_free(pointer1);
	*pointer1 = NULL;
	ft_free(pointer2);
	*pointer2 = NULL;
	pointers_num -= 2;
	while (pointers_num-- > 0)
	{
		pointer = va_arg(ap, unsigned char **);
		ft_free((void **)pointer);
		*pointer = NULL;
	}
}
