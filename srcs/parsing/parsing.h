#ifndef PARSING_H
# define PARSING_H

#include "../../includes/minishell.h"

t_command	*token_to_ast(t_token *token);
t_command		*init_command(t_parsing *data);
int				add_words_to_command(t_parsing *data);
int				add_redirection(t_parsing *data);
int				add_redirection_to_data(t_parsing *data, int type);
int				type_to_oflags(int type);
t_redirection	*init_redirection(t_parsing *data, int type, int o_flags);
t_redirection	*last_redirection(t_redirection *redirection);
t_command		*init_operator(t_parsing *data, t_command *left_command);
int				token_to_operator_type(t_token *token);

// here_docs

int			add_here_doc_to_data(t_parsing *data);
t_here_doc	*init_here_doc(t_parsing *data);
t_here_doc	*last_here_doc(t_parsing *data);

#endif