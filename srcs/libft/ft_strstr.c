/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:57:19 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/31 18:58:00 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	char	*retval;

	i = 0;
	j = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (big[i])
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && big[i + j] && little[j])
			{
				if (j + 1 == ft_strlen((char *)little))
					return (retval = (char *)&big[i], retval);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
