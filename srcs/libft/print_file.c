/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:12:30 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/04 22:12:31 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*	Print the content of the file pointed by fd
Return 1 if an Error occurs, and 0 otherwise*/
int	print_file(int fd)
{
	char	*file;

	file = read_file(fd);
	if (file == NULL)
		return (EXIT_FAILURE);
	if (ft_putstr_fd(file, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
