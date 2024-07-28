/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:19:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 00:12:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstiter(t_token *lst, void (*f)(void *))
{
	t_token	*node;

	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}
