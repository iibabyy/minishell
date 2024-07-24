/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:14:29 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	long	c;
	int		check;

	c = (long)n;
	check = 0;
	if (c < 0)
	{
		check += ft_putchar_fd('-', fd);
		c = -c;
	}
	if (c >= 10)
	{
		check += ft_putnbr_fd((c / 10), fd);
		check += ft_putnbr_fd((c % 10), fd);
	}
	else if (c <= 9)
	{
		check += ft_putchar_fd((c + 48), fd);
	}
	return (check);
}

/*#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_putnbr_fd(atoi(av[1]), 1);
	return (0);
}
*/

/*int		main(int argc, const char *argv[])
{
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		ft_putnbr_fd(0, 2);
	else if (arg == 2)
		ft_putnbr_fd(5, 1);
	else if (arg == 3)
		ft_putnbr_fd(-5, 2);
	else if (arg == 4)
		ft_putnbr_fd(42, 1);
	else if (arg == 5)
		ft_putnbr_fd(-57, 2);
	else if (arg == 6)
		ft_putnbr_fd(164189, 1);
	else if (arg == 7)
		ft_putnbr_fd(-987441, 2);
	else if (arg == 8)
		ft_putnbr_fd(2147483647, 1);
	else if (arg == 9)
		ft_putnbr_fd(-2147483648LL, 2);
	return (0);
}*/