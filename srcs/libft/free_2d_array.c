/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:05:57 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/05 23:29:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	free_2d_array(void ***NULL_terminated_2d_array)
{
	int	i;

	i = 0;
	if (!(*NULL_terminated_2d_array))
		return ;
	while ((*NULL_terminated_2d_array)[i])
	{
		ft_free((*NULL_terminated_2d_array)[i]);
		i++;
	}
	ft_free((void *)*NULL_terminated_2d_array);
	(*NULL_terminated_2d_array) = NULL;
}
