/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:16 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/19 22:53:25 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*retval;

	i = 0;
	while (str[i] && str[i] != (unsigned char)c)
		i++;
	if (str[i] == '\0' && (unsigned char)c != '\0')
		return (retval = 0);
	retval = (char *)str + i;
	return (retval);
}
