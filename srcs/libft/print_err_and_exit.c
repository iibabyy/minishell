/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_and_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:11:17 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	print_err_and_exit(const char *err, int code, bool erno)
{
	if (erno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd((char *)err, 1);
	}
	exit(code);
}
