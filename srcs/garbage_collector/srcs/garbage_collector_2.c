/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:34:36 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/07 16:36:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb_utils.h"

/*
lock the addresse if allocated by ft_malloc() function,
the clear_garbage() function don't free() the locked adresses.
the desrtoy_garbage() function does free the locked addresses
*/
void	lock(void *address)
{
	t_garb_node	*node;
	t_garbage	*garbage;

	if (address == NULL)
		return ;
	garbage = get_garbage(NULL, GETTER);
	if (garbage == NULL)
		return ;
	node = find_by_address(address, garbage);
	if (node == NULL)
		return ;
	node->locked = true;
}

/*
unlock the addresse if allocated by ft_malloc() function,
the clear_garbage() function can't free() the locked adresses.
*/
void	unlock(void *address)
{
	t_garb_node	*node;
	t_garbage	*garbage;

	if (address == NULL)
		return ;
	garbage = get_garbage(NULL, GETTER);
	if (garbage == NULL)
		return ;
	node = find_by_address(address, garbage);
	if (node == NULL)
		return ;
	node->locked = false;
}
