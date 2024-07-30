#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

#include "../../includes/minishell.h"

t_command		*init_command(void);
int				add_words_to_command(t_parsing *data);
int				add_redirections_to_command(t_parsing *data);
int				type_to_oflags(int type);
t_redirection	*init_redirection(t_parsing *data, int type, int o_flags);
t_redirection	*find_last_redirection(t_redirection *redirection);

// here_docs

int			add_here_doc_to_data(t_parsing *data);
t_here_doc	init_here_doc(t_parsing *data);
t_here_doc	*find_last_here_doc(t_parsing *data);

#endif