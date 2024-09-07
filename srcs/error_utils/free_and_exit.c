/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/07 15:19:29 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

void	free_and_exit(char *err, int status, struct s_data *data, bool erno)
{
	free_all(data);
	if (err != NULL || erno == true)
		print_err(err, erno);
	exit(status);
}

void	free_all(t_data *data)
{
	(void)data;
	destroy_garbage();
}

void	print_err_and_exit(char *err, int status, bool erno)
{
	print_err(err, erno);
	exit(status);
}
