/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:26:41 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:29:43 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexing.h"

void	tab_to_spaces(char *input)
{
	int		i;

	if (input == NULL)
		return ;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\t')
			input[i] = ' ';
	}
}
