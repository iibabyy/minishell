/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:14:29 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/04 22:13:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	put_more_than_10(int c, int fd);

int	ft_putnbr_fd(int n, int fd)
{
	long	c;
	int		check;
	int		temp;

	(c = (long)n, check = 0, temp = 0);
	if (c < 0)
	{
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		(++check, c = -c);
	}
	if (c >= 10)
	{
		temp = put_more_than_10(c, fd);
		if (temp == -1)
			return (-1);
		check += temp;
	}
	else if (c <= 9)
	{
		if (ft_putchar_fd((c + 48), fd) == -1)
			return (-1);
		++check;
	}
	return (check);
}

static int	put_more_than_10(int c, int fd)
{
	int	temp;
	int	check;

	temp = 0;
	check = 0;
	temp = ft_putnbr_fd((c / 10), fd);
	if (temp == -1)
		return (-1);
	check += temp;
	temp = ft_putnbr_fd((c % 10), fd);
	if (temp == -1)
		return (-1);
	check += temp;
	return (check);
}
