/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:28:45 by mdembele          #+#    #+#             */
/*   Updated: 2024/06/23 17:29:00 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(void ***str)
{
	size_t	i;

	i = 0;
	if ((*str) == NULL)
		return ;
	while ((*str)[i] != NULL)
	{
		ft_free((void **)&(*str)[i]);
		i++;
	}
	ft_free((void **)str);
	return ;
}
