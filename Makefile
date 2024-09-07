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

INCLUDE_DIR = includes/

FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3

SRCS_DIR = srcs/

# Libft

LIBFT_DIR = srcs/libft/

LIBFT = $(LIBFT_DIR)libft.a

# Garbage Collector

GARBAGE_COLLECTOR_DIR = srcs/garbage_collector/

GARBAGE_COLLECTOR = $(GARBAGE_COLLECTOR_DIR)garbage_collector.a

# Minishell

FILES =	srcs/Minishell/minishell.c			\
		srcs/Minishell/utils.c				\
		srcs/Minishell/test_utils.c			\
		srcs/error_utils/free_and_exit.c	\
		srcs/error_utils/print_err.c		\
		srcs/error_utils/free_utils.c		\
		srcs/lexing/check_char.c			\
		srcs/lexing/lexing.c				\
		srcs/lexing/lexing_utils.c			\
		srcs/lexing/lexing_utils_2.c		\
		srcs/lexing/env_var.c				\
		srcs/parsing/parsing_utils.c		\
		srcs/parsing/here_doc.c				\
		srcs/parsing/parsing.c				\
		srcs/parsing/redirection_utils.c	\
		srcs/parsing/redirections.c			\
		srcs/parsing/utils.c				\
		srcs/exec/exec.c					\
		srcs/exec/exec_utils.c              \
		srcs/exec/create_path.c             \
		srcs/exec/signal.c					\
		srcs/features/alias_utils.c			\
		srcs/features/aliases.c				\
		srcs/built_in/env_utils_1.c			\
		srcs/built_in/env_utils_2.c			\
		srcs/built_in/env.c					\
		srcs/built_in/export.c				\
		srcs/built_in/unset.c				\
		srcs/features/history.c				\
		srcs/features/prompt.c				\
		srcs/exec/signal_utils.c			\
		srcs/built_in/pwd.c					\
		srcs/built_in/cd.c					\

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
	@$(CC) $(FLAGS) $(OBJ) $(GARBAGE_COLLECTOR) -lreadline $(LIBFT) -o $(NAME)
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
	@rm -f .error_log
	@echo "$(BLUE)Minishell cleaned ! ✅$(END)"

ac : all clean

re :
	@make -s fclean
	@echo ""
	@make -s all

s :
	@make -sC $(LIBFT_DIR)
	@make -sC $(GARBAGE_COLLECTOR_DIR)
	@make -s

res :
	@make re -sC $(LIBFT_DIR)
	@make re -sC $(GARBAGE_COLLECTOR_DIR)
	@make -s

.PHONY: all re clean fclean ac s res
