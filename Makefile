#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3

INCLUDE_DIR = includes/

SRCS_DIR = srcs/

# Libft

LIBFT_DIR = srcs/libft/

LIBFT = $(LIBFT_DIR)libft.a

# Garbage Collector

GARBAGE_COLLECTOR_DIR = srcs/garbage_collector/

GARBAGE_COLLECTOR = $(GARBAGE_COLLECTOR_DIR)garbage_collector.a

# Minishell

FILES =	srcs/minishell/error_utils/free_and_exit.c	\
		srcs/minishell/error_utils/print_err.c		\

OBJ = $(FILES:.c=.o)

all	: $(NAME)

# Variables

$(NAME) : $(LIBFT) $(GARBAGE_COLLECTOR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(GARBAGE_COLLECTOR) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) done ! ✅$(END)"

$(GARBAGE_COLLECTOR) : $(GARBAGE_COLLECTOR_DIR)
	@make -sC $(GARBAGE_COLLECTOR_DIR)

$(LIBFT) : $(LIBFT_DIR)
	@make -sC $(LIBFT_DIR)

# Compilation

%.o : %.c
	@echo "$(BLUE)Compiling: $^$(END)"
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@make clean -sC $(LIBFT_DIR)
	@make clean -sC $(GARBAGE_COLLECTOR_DIR)
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -sC $(LIBFT_DIR)
	@make fclean -sC $(GARBAGE_COLLECTOR_DIR)
	@rm -f $(NAME)
	@echo "$(GREEN)Minishell cleaned ! ✅$(END)"

re : fclean all

.PHONY: all re clean fclean