#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#


SRCS =	srcs/garbage_utils.c		\
		srcs/garbage_collector.c	\

NAME = ./garbage_collector.a

OBJS = $(SRCS:.c=.o)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -O3

all: $(NAME)

%.o : %.c
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS)
	@ar cr $(NAME) $(OBJS)
	@echo "$(GREEN)Garbage Collector library done ✅$(END)"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Garbage Collector library cleaned $(END)"

re: clean fclean all