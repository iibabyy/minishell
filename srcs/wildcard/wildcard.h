#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../includes/minishell.h"
# include "../lexing/lexing.h"

char	*list_files(char *str, char **input);
bool	is_valid_name(char *name, char *original, char **input);

#endif