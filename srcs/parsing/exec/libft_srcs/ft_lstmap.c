/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:46:07 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/23 22:05:17 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*list;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}

/*void *change_capitalization(void *str) {
	char *s = (char *)str;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] -= 32;
		}
	}
	return ((void *)s);
}

void	print_list(t_list *lst) {
	while (lst) {
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

void	del_content(void *content) {
	free(content);
}

int	main(void) {
	t_list *lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(strdup("hello")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("world")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("openai")));

	printf("Liste initiale : ");
	print_list(lst);

	t_list *new_lst = ft_lstmap(lst, &change_capitalization, &del_content);
	printf("Nouvelle liste avec la capitalisation modifiée : ");
	print_list(new_lst);
	ft_lstclear(&new_lst, &del_content);

	return (0);
}*/
