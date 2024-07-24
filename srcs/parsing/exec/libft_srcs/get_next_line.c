/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:27 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/06 21:27:38 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_leftline(char *stash, char *temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	if (temp[i] != '\0')
	{
		while (temp[i])
			stash[j++] = temp[i++];
		stash[j] = '\0';
	}
}

size_t	ft_str_len(const char *str, char c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

void	ft_clean(char *victim)
{
	size_t	i;

	i = 0;
	if (victim)
	{
		while (victim[i] != '\n' && victim[i])
		{
			victim[i] = '\0';
			i++;
		}
		ft_gnlstrlcpy(victim, victim + i + 1, ft_str_len(victim, '\0'));
	}
}

char	*findln(int fd, char *stash)
{
	int		nbytes;
	char	*buff1;
	char	*stock;

	nbytes = 1;
	buff1 = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff1)
		return (NULL);
	stock = ft_strdup(stash);
	if (!stock)
		return (free(buff1), NULL);
	while (nbytes > 0 && ft_gnlstrchr(stock, '\n') == NULL)
	{
		nbytes = read(fd, buff1, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(buff1), free(stock), NULL);
		buff1[nbytes] = '\0';
		stock = ft_gnlstrjoin(stock, buff1);
		if (nbytes == 0 && *stock == '\0')
			return (free(buff1), free(stock), NULL);
	}
	return (free(buff1), stock);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*nextline;
	char		*full;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (fd >= 0 && read(fd, NULL, 0) < 0 && *stash)
		{
			nextline = ft_strdup(stash);
			if (!nextline)
				return (NULL);
			return (nextline);
		}
		ft_clean(stash);
		return (NULL);
	}
	full = findln(fd, stash);
	if (!full)
		return (NULL);
	free((ft_clean(stash), ft_leftline(stash, full), NULL));
	nextline = malloc(sizeof(char) * ft_str_len(full, '\n') + 1);
	if (!nextline)
		return (free(full), NULL);
	ft_cpynl(nextline, full);
	return (free(full), nextline);
}
/*int main(void)
{
	int fd;
	char	*line;

	fd = open("41_with_nl", O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if(line ==  NULL)
			break ;
	}
	close(fd);
}*/