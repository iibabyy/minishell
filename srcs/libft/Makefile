#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

SRCS =	count_char.c			\
		count_char_2d.c			\
		free_2d_array.c			\
		ft_atoi.c				\
		ft_atol.c				\
		ft_bzero.c				\
		ft_calloc.c				\
		ft_close_fd.c			\
		ft_isalnum.c			\
		ft_isalpha.c			\
		ft_isascii.c			\
		ft_isdigit.c			\
		ft_isprint.c			\
		ft_itoa.c				\
		ft_lstadd_back.c		\
		ft_lstadd_front.c		\
		ft_lstclear.c			\
		ft_lstdelone.c			\
		ft_lstiter.c			\
		ft_lstlast.c			\
		ft_lstmap.c				\
		ft_lstnew.c				\
		ft_lstsize.c			\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_memcpy.c				\
		ft_memmove.c			\
		ft_memset.c				\
		ft_multi_free.c			\
		ft_putchar_fd.c			\
		ft_putendl_fd.c			\
		ft_putnbr_fd.c			\
		ft_putstr_fd.c			\
		ft_re_strdup.c			\
		ft_re_strjoin.c			\
		ft_realloc.c			\
		ft_split.c				\
		ft_strchr.c				\
		ft_strcmp.c				\
		ft_strdup.c				\
		ft_striteri.c			\
		ft_strjoin.c			\
		ft_strlcat.c			\
		ft_strlcpy.c			\
		ft_strlen.c				\
		ft_strmapi.c			\
		ft_strncmp.c			\
		ft_strnstr.c			\
		ft_strrchr.c			\
		ft_strtrim.c			\
		ft_substr.c				\
		ft_tolower.c			\
		ft_toupper.c			\
		multi_re_strjoin.c		\
		multi_strjoin.c			\
		print_2d_array_nl.c		\
		print_err_and_exit.c	\
		str_join_2d.c			\
		str_join_2d_and_free.c	\
		print_2d_array.c		\
		ft_remove_char.c		\
		ft_re_remove_char.c		\
		get_next_line_utils.c 	\
		get_next_line.c			\
		read_file.c 			\
		re_join_gnl.c			\
		print_file.c			\
		ft_strlen_2d.c 			\
		insert_str.c			\
		ft_strstr.c				\
		2dstr_join.c			\
		sort_str2d.c			\

#	Loading bar	#

G                = \e[92m
X                 = \e[0m
BAR_SIZE        = 75

TOTAL_FILES        := $(words $(SRCS))
COMPILED_FILES    := 0

#				#

NAME = libft.a
OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3 -fPIE

all: Makefile $(NAME)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n " "
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " [$(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%] "
# @echo -n "["
# @printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
# @echo -n "] "
# @printf "%s" $(notdir $<)
	@printf "\e[0K\r"
	
$(NAME): $(OBJECTS_PREFIXED) $(SRCS)
	@ar cr $(NAME) $(OBJECTS_PREFIXED)
	@echo ""
	@echo "$(BLUE)Libft done ✅$(END)"
	@echo ""

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean all