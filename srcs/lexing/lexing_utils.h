#ifndef LEXING_UTILS_H
# define LEXING_UTILS_H

#include <stdbool.h>

# include "../../includes/structs.h"
# include "../../includes/error.h"
# include "../../includes/libft.h"
# include "../../includes/garbage_collector.h"

bool	is_meta_char(char *input, int index);
bool	is_operator(char *input, int index);
bool	is_redirection(char c);
bool	is_quotes(char c);
int		metachar_size(char *input, int start);

#endif