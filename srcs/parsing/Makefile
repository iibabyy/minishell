NAME		=	minishell


LIBFT		=	libft_srcs/libft.a

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra

SRCS		=	main.c \
				parsing.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft_srcs

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft_srcs

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft_srcs

re			:	fclean all