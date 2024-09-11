#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../includes/minishell.h"
# include "../lexing/lexing.h"

char	*list_files(char *str);
bool	is_valid_name(char *name, char *original);

#endif