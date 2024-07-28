/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:31:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/28 01:44:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garb_node
{
	void				*address;
	struct s_garb_node	*next;
}	t_garb_node;

typedef struct s_garbage
{
	t_garb_node	*first;
}	t_garbage;

void	*ft_malloc(unsigned long size);
void	ft_free(void **address);
void	destroy_garbage(t_garbage *only_for_init);

#endif