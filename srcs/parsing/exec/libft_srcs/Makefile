# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdembele <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 15:39:26 by mdembele          #+#    #+#              #
#    Updated: 2024/07/05 19:53:37 by mdembele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
       ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
       ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
       ft_putnbr_fd.c ft_putstr_fd.c ft_printabln.c  get_next_line.c \
       ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c  get_next_line_utils.c\
       ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
       ft_strrchr.c ft_strtrim.c ft_re_strjoin.c ft_free.c ft_free_2d.c \
       ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_strnstr.c \

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c \
              ft_lstadd_back.c ft_lstiter.c ft_lstmap.c \
              ft_lstclear.c ft_lstdelone.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	ar rc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -include ./libft.h $< -o $@


bonus: all $(OBJS_BONUS)
	ar rc $(NAME) $(OBJS_BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -c -include ./libft.h $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
