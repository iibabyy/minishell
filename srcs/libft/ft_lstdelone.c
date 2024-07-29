/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:20:12 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 15:15:35 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	ft_free(lst);
}
