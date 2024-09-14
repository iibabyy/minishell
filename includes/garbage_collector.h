/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:31:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:36:32 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "structs.h"

void	*ft_malloc(unsigned long size);
void	*ft_realloc(void *ptr, unsigned long size_to_add);
void	ft_free(void *address);
void	destroy_garbage(void);
void	clear_garbage(void);
void	lock(void *address);
void	unlock(void *address);

#endif