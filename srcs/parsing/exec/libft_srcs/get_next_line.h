/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:58:19 by mdembele          #+#    #+#             */
/*   Updated: 2024/07/05 19:58:54 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct gnlvalue
{
	char	*buff;
	char	*temp;
	char	*str;
	char	*line;
}			t_gnlvalue;

size_t		ft_gnlstrlcpy(char *dest, const char *src, size_t destsize);
void		ft_cpynl(char *dest, char *src);
char		*get_next_line(int fd);
char		*ft_gnlstrjoin(const char *s1, const char *s2);
char		*ft_gnlstrchr(const char *s, int c);
size_t		ft_str_len(const char *str, char c);
#endif
