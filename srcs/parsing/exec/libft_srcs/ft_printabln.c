/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printabln.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:26:29 by mdembele          #+#    #+#             */
/*   Updated: 2024/06/23 17:27:28 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_printabln(char **str, int fd)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		ft_putstr_fd(str[j], fd);
		write(fd, "\n", 1);
		j++;
	}
}
