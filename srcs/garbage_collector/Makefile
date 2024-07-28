#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

SRCS_DIR = srcs/

SRCS =	$(SRCS_DIR)garbage_utils.c		\
		$(SRCS_DIR)garbage_collector.c	\

NAME = ./garbage_collector.a

OBJS = $(SRCS:.c=.o)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -O3

all: $(NAME)

%.o : %.c
	@echo "$(BLUE)compiling: $(patsubst $(SRCS_DIR)%,%, $<)$(END)"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS)
	@ar cr $(NAME) $(OBJS)
	@echo "$(GREEN)Garbage Collector done ✅$(END)"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)Garbage Collector cleaned ! ✅$(END)"

re: clean fclean all