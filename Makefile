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

FLAGS = -Wall -Wextra -Werror -g3

INCLUDE_DIR = includes/

SRCS_DIR = srcs/

FILES =	$(addprefix $(SRCS_DIR), \
				garbage_collector/garbage_collector.c	\
		)

OBJ = $(FILES:.c=.o)

all	: $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
		@echo "$(GREEN)$(NAME) done ! ✅$(END)"

%.o : %.c
		@echo "$(BLUE)Compiling: $^$(END)"
		@$(CC) $(FLAGS) -c $< -o $@
clean :
	@rm -rf $(OBJ)
	@echo "$(RED)objects removed$(END)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(END)"
	@echo "$(GREEN)cleaned ! ✅$(END)"

re : fclean all

.PHONY: all re clean fclean