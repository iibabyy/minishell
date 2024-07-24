/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:18:25 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/24 20:58:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

/*
static void	ft_lstiter2(t_list *lst, void *(*f)(void *))
{
	t_list	*node;

	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}

static t_list	*ft_lstdup(t_list *lst)
{
	t_list	*originalnode;
	t_list	*newnode;
	t_list	*newhead;

	if (!lst)
		return (NULL);
	if (!(newhead = malloc(sizeof(t_list))))
		return (NULL);
	newhead = lst;
	originalnode = lst->next;
	while (originalnode)
	{
		if (!(newnode = ft_lstnew(originalnode->content)))
			return (NULL);
		ft_lstadd_back(&newhead, newnode);
		originalnode = originalnode->next;
	}
	return (newhead);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;

	if (!(newlist = ft_lstdup(lst)))
	{
		ft_lstclear(&newlist, del);
		return (NULL);
	}
	ft_lstiter2(newlist, f);
	return (newlist);
}
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	if (!lst)
		return (0);
	new_lst = 0;
	while (lst)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}
