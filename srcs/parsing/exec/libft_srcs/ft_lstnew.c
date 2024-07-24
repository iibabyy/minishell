/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:45:51 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:45:53 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = malloc(sizeof(t_list));
	if (!(lstnew))
		return (NULL);
	lstnew->content = content;
	lstnew->next = NULL;
	return (lstnew);
}
