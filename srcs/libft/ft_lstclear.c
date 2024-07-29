/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:20:27 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 15:12:04 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*elm;
	t_token	*tmp;

	elm = *lst;
	while (elm)
	{
		tmp = elm->next;
		ft_lstdelone(elm, del);
		elm = tmp;
	}
	*lst = NULL;
}
