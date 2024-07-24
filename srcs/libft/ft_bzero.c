/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:33:26 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>

void	ft_bzero(void *array, size_t lim)
{
	ft_memset(array, 0, lim);
}

/*
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	check_bzero(void *mem, int c, int len, int n_bzero)
{
	memset(mem, c, len);
	ft_bzero(mem, n_bzero);
	write(1, mem, len);
}

int	main(int argc, const char *argv[])
{
	void	*mem;
	int		len;
	int		arg;

	alarm(5);
	len = 5;
	if (argc == 1 || !(mem = malloc(sizeof(*mem) * len)))
		return (0);
	if ((arg = atoi(argv[1])) == 1)
		check_bzero(mem, 'e', len, 5);
	else if (arg == 2)
		check_bzero(mem, 'e', len, 0);
	free(mem);
	return (0);
}
*/