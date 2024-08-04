#ifndef	MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>

#include "structs.h"
#include "libft.h"
#include "garbage_collector.h"
#include "error.h"

// features

int	init_aliases();
int	replace_aliases(t_command *last_command);


// lexing

char		*replace_env_vars(char *input);
t_token		*input_to_tokens(char *input);
char		*get_input(char *end_of_file, char *prompt, bool quotes);

// parsing

t_command	*parse(char	*input);
int			open_redirections(t_command	*command);
t_command	*last_command(t_command *current);

// debug

char 		*type_to_str(int type);
char		 *operator_type_to_str(int type);

#endif