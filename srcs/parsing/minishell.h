#ifndef MINISHELL_H
#define MINISHELL_H

#include "exec/libft_srcs/libft.h"
#include "parsing.h"

#define CMD    0
#define PIPE   1
#define ARGS   2
#define AND    3
#define OR     4
#define HERE_DOC 5
#define APPEND   6


typedef struct s_comand
{
	int type;
	char *data;
	char **args;
	struct s_comand *next;
	struct s_comand *previous;
}				t_comand;

int checking_line(char  *line);



#endif