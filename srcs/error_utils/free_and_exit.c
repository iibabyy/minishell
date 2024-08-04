/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/04 22:05:43 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

void	free_and_exit(char *err, int status, struct s_data *data, bool errno)
{
	free_all(data);
	if (err != NULL || errno == true)
		print_err(err, errno);
	exit(status);
}

void	free_all(t_data *data)
{
	(void)data;
	destroy_garbage(NULL);
}
