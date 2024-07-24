/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:47:22 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 20:51:38 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*ft_rvtab(char *str)
{
	int		fin;
	int		debut;
	char	temp[1];

	fin = ft_strlen(str) - 1;
	debut = 0;
	while (fin > debut)
	{
		temp[0] = str[fin];
		str[fin] = str[debut];
		str[debut] = temp[0];
		fin--;
		debut++;
	}
	return (str);
}

static int	ft_count_units(long int n)
{
	int	i;

	i = 2;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	exec(long int nb, char *itoa)
{
	int	i;
	int	isneg;

	i = 0;
	isneg = 0;
	if (nb < 0)
	{
		nb = nb * (-1);
		isneg = 1;
	}
	while (nb != 0)
	{
		itoa[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (isneg == 1)
	{
		itoa[i] = '-';
		i++;
	}
	itoa[i] = '\0';
}

char	*ft_itoa(int n)
{
	char		*itoa;
	long int	nb;

	nb = n;
	itoa = malloc(sizeof(char) * ft_count_units(nb));
	if (!(itoa))
		return (NULL);
	if (nb == 0)
	{
		itoa[0] = '0';
		itoa[1] = '\0';
		return (itoa);
	}
	exec(nb, itoa);
	ft_rvtab(itoa);
	return (itoa);
}
