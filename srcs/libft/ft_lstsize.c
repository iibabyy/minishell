/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:17:12 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 00:12:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_lstsize(t_token *lst)
{
	int		i;
	t_token	*count;

	i = 1;
	if (!lst)
		return (0);
	count = lst->next;
	while (count)
	{
		count = count->next;
		i++;
	}
	return (i);
}
