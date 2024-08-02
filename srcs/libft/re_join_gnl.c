/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:11:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/01 07:53:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*re_join_gnl(int fd, char *str_address)
{
	char	*gnl;

	gnl = get_next_line(fd);
	if (gnl == NULL)
		return (ft_free(str_address), NULL);
	if (str_address == NULL)
		return (gnl);
	gnl = ft_re_strjoin(str_address, gnl);
	return (gnl);
}
