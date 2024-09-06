/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:20:39 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:51:49 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../../includes/libft.h"

#ifndef MAX_FD
# define MAX_FD 100
#endif

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	save[MAX_FD][BUFFER_SIZE + 1] = {0};
	char		*str;
	int			byte_read;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	byte_read = 1;
	str = ft_strdup(save[fd]);
	buffer = ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (ft_free(buffer), ft_free(str),
			malloc_failed("get_next_line"), NULL);
	while (is_newline(str) == 0 && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (ft_clean(save[fd]), ft_free(buffer), ft_free(str), NULL);
		buffer[byte_read] = '\0';
		str = ft_re_strjoin(str, buffer);
		if (!str)
			return (ft_free(buffer), NULL);
	}
	(after_line(str, save[fd]), str = re_before_line(str));
	return (ft_free(buffer), str);
}

void	ft_clean(char *save)
{
	size_t	i;

	i = 0;
	if (!*save)
		return ;
	while (save[i] != '\n' && save[i])
	{
		save[i] = '\0';
		i++;
	}
	ft_strlcpy(save, save + i + 1, BUFFER_SIZE + 1);
}

void	after_line(char *str, char *save)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	else
	{
		*save = '\0';
		return ;
	}
	ft_strlcpy(save, str + i, BUFFER_SIZE + 1);
}

char	*re_before_line(char *all)
{
	int		i;
	char	*dest;
	int		test;

	i = 0;
	if (!all)
		return (NULL);
	while (all[i] != '\n' && all[i])
		i++;
	if (all[i] == '\n')
		i++;
	if (i == 0 && all[i] == '\0')
		return (NULL);
	dest = ft_malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (ft_free(all), malloc_failed("re_before_line"), NULL);
	test = i;
	while (i >= 0)
	{
		dest[i] = all[i];
		i--;
	}
	dest[test] = '\0';
	return (ft_free(all), dest);
}
