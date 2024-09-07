/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:33:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:42:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

static int	numlen(int num)
{
	int	i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static void	reversetab(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i++] = str[j];
		str[j--] = temp;
	}
}

void	reverse(char *str, int sign, int n)
{
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else if (sign >= 0)
		reversetab(str);
	else
	{
		reversetab(str + 1);
		str[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	long	c;
	char	*str;

	sign = 1;
	i = 0;
	c = (long)n;
	if (n < 0)
	{
		sign = -sign;
		c = -c;
		i = 1;
	}
	str = ft_malloc(sizeof(char) * (numlen(c) + 5));
	if (!str)
		return (malloc_failed("ft_itoa"), NULL);
	while (c)
	{
		str[i++] = c % 10 + '0';
		c /= 10;
	}
	str[i] = '\0';
	reverse(str, sign, n);
	return (str);
}
