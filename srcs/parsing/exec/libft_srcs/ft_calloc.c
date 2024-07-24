/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:48:09 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 22:49:25 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void		*s;
	long long	test;

	test = elementCount + elementSize;
	if ((long long)elementSize + (long long)elementCount != test
		|| ((long long)elementCount < 0 && (long long)elementSize < 0))
		return (NULL);
	if ((long long)elementCount * (long long)elementSize < 0)
		return (NULL);
	s = malloc(elementSize * elementCount);
	if (!(s))
		return (NULL);
	ft_bzero(s, elementCount * elementSize);
	return (s);
}
