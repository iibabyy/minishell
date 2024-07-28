/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:17:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 01:30:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

t_token	*ft_lstnew(char *content)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
