/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:35:02 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/29 15:16:31 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

#include "garbage_collector.h"
#include "structs.h"

void		ft_close_fd(int *fd);
char		*ft_re_strjoin(const char *s1, const char *s2);
void		free_2d_array(void ***NULL_terminated_2d_array);
char		*ft_re_strdup(char *src);
char		*multi_strjoin(int strings_number, char *s1, char *s2, ...);
char		*multi_re_strjoin(int strings_number, char *s1, char *s2, ...);
void		ft_multi_free(int pointers_num, void **ptr1, void **ptr2, ...);
int			print_2d_array_nl(char **NULL_TERMINATED_ARRAY);
char		*re_join_get_next_line(int fd, char **str_address);
int			count_char(char *str, char char_to_count);
int			count_char_2d(char **array, char char_to_count);
void		*ft_realloc(void *buffer, int buffer_size,
				size_t new_size, size_t sizeof_type);
long int	ft_atol(const char *str);

int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putendl_fd(char *s, int fd);

int			ft_isascii(char c);
int			ft_isalnum(char c);
int			ft_isalpha(char c);
int			ft_isdigit(char c);
int			ft_isprint(char c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_bzero(void *array, size_t lim);

void		*ft_memset(void *adress, int value, size_t hmany);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *str, int tofind, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);

void		*ft_calloc(size_t count, size_t size);
char		**ft_split(const char *s, char sep);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);

char		*ft_itoa(int c);
int			ft_atoi(const char *str);

char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlcpy(char *dest, const char *source, size_t dest_size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *big, const char *little, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlen(const char *str);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

t_token		*ft_lstnew(char *content);
void		ft_lstadd_front(t_token **lst, t_token *new);
int			ft_lstsize(t_token *lst);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstdelone(t_token *lst, void (*del)(void *));
void		ft_lstclear(t_token **lst, void (*del)(void *));
void		ft_lstiter(t_token *lst, void (*f)(void *));
t_token		*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *));

#endif