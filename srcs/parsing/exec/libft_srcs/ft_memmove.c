/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:54:27 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 21:33:33 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	const unsigned char	*n_src;
	unsigned char		*n_dest;
	size_t				i;

	i = size;
	n_src = (const unsigned char *)src;
	n_dest = (unsigned char *)dest;
	if (src < dest)
	{
		while (i--)
			n_dest[i] = n_src[i];
	}
	else
		ft_memcpy(n_dest, n_src, size);
	return (n_dest);
}

/*int main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;

	dest = src + 1;
	if (dest != ft_memmove(dest, src, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
}
*/
