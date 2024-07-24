/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:14 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>

void	*ft_memset(void *adress, int value, size_t hmany)
{
	unsigned char	*tab;

	tab = adress;
	while (hmany--)
		*tab++ = value;
	return (adress);
}
