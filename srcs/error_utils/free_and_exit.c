/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/10 20:17:02 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

void	free_and_exit(int status)
{
	free_all();
	exit(status);
}

void	free_all(void)
{
	destroy_garbage();
}

void	print_err_and_exit(char *err, int status, bool erno)
{
	print_err(err, erno);
	free_and_exit(status);
}
