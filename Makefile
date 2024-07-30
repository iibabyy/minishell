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

FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3 -O3

INCLUDE_DIR = includes/

SRCS_DIR = srcs/

# Libft

LIBFT_DIR = srcs/libft/

LIBFT = $(LIBFT_DIR)libft.a

# Garbage Collector

GARBAGE_COLLECTOR_DIR = srcs/garbage_collector/

GARBAGE_COLLECTOR = $(GARBAGE_COLLECTOR_DIR)garbage_collector.a

# Minishell

FILES =	srcs/error_utils/free_and_exit.c	\
		srcs/error_utils/print_err.c		\
		srcs/error_utils/free_utils.c		\
		srcs/lexing/check_char.c			\
		srcs/lexing/lexing.c				\
		srcs/lexing/test.c					\
		srcs/lexing/lexing_utils.c			\

OBJ = $(FILES:.c=.o)

#	Loading bar	#

G                = \e[92m
X                 = \e[0m
BAR_SIZE        = 75

TOTAL_FILES        := $(words $(FILES))
COMPILED_FILES    := 0

#				#

all	: $(NAME)

# Variables

$(NAME) : $(LIBFT) $(GARBAGE_COLLECTOR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(GARBAGE_COLLECTOR) $(LIBFT) -o $(NAME)
	@echo ""
	@echo "$(BLUE)$(NAME) done ! ✅$(END)"

$(GARBAGE_COLLECTOR) : $(GARBAGE_COLLECTOR_DIR)
	@make -sC $(GARBAGE_COLLECTOR_DIR)

$(LIBFT) : $(LIBFT_DIR)
	@make -sC $(LIBFT_DIR)

# Compilation

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n " "
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " ($(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%) "
	@echo -n "["
	@printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
	@echo -n "] "
	@printf "%s" $(notdir $<)
	@printf "\e[0K\r"

clean :
	@make clean -sC $(LIBFT_DIR)
	@make clean -sC $(GARBAGE_COLLECTOR_DIR)
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -sC $(LIBFT_DIR)
	@make fclean -sC $(GARBAGE_COLLECTOR_DIR)
	@rm -f $(NAME)
	@echo "$(BLUE)Minishell cleaned ! ✅$(END)"

re : fclean all

.PHONY: all re clean fclean