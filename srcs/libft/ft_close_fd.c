/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:22:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/03 01:18:29 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>
#include "../../includes/error.h"

void	ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		error_log("ft_close_fd: close() failed:", true);
	*fd = -1;
}
