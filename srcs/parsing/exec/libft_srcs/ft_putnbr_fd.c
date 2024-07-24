/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:34 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/20 21:35:30 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long long int	v;

	v = n;
	if (v < 0)
	{
		ft_putchar_fd('-', fd);
		v *= -1;
	}
	if (v >= 0 && v <= 9)
		ft_putchar_fd(v + '0', fd);
	else
	{
		ft_putnbr_fd(v / 10, fd);
		ft_putchar_fd(v % 10 + '0', fd);
	}
}
