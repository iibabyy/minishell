#ifndef PARSING_H
# define PARSING_H

#include "../../includes/minishell.h"

t_command		*token_to_ast(t_parsing *data);
t_command		*init_command(t_parsing *data);
int				add_words_to_command(t_parsing *data);
int				add_redirection(t_parsing *data);
int				add_redirection_to_data(t_parsing *data, int type);
int				type_to_oflags(int type);
t_redirection	*init_redirection(t_parsing *data, int type, int o_flags);
t_redirection	*last_redirection(t_redirection *redirection);
t_command		*init_operator(t_parsing *data, t_command *left_command);
int				token_to_operator_type(t_token *token);
int				check_redirection(t_redirection	*redirection);
int				open_redirections(t_redirection	*redirection);
t_redirection	*parse_redirections(t_redirection *redirection);
int				open_file(t_redirection *redirection);
int				args_number(t_token *token);
int				redirections_number(t_token *token);

// here_docs

t_here_doc	*init_here_doc(t_parsing *data);
int	open_here_doc(t_redirection *redirection);

#endif