#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

#include "../../includes/minishell.h"

t_command	*init_command(void);
int			add_words_to_command(t_parsing *data);
int			add_redirections_to_command(t_parsing *data);
int			add_output(t_parsing *data);
int			add_output_append(t_parsing *data);
int			add_input(t_parsing *data);

// here_docs

int			add_here_doc(t_parsing *data);
t_here_doc	init_t_here_doc(t_parsing *data);
t_here_doc	*find_last_here_doc(t_parsing *data);

#endif