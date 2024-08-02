/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_2d_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:28:34 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/02 20:06:54 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*str_join_2d_and_free(char **str_2d, char *sep)
{
	char	*str;

	if (str_2d == NULL)
		return (NULL);
	str = str_join_2d(str_2d, sep);
	free_2d_array((void ***)&str_2d);
	return (str);
}
