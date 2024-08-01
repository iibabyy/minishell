#ifndef PARSING_H
# define PARSING_H

#include "../../includes/minishell.h"

/*  Priorities	*/

# define SUB_SH_WEIGHT 3
# define PIPE_WEIGHT 2
# define AND_WEIGHT 1
# define OR_WEIGHT 1
# define HEREDOC_PROMPT "heredoc> "

t_command		*token_to_ast(t_parsing *data);
t_command		*create_ast(t_parsing *data, t_command *left);
t_command		*init_command(t_parsing *data);
int				add_words_to_command(t_parsing *data);
int				add_redirection(t_parsing *data);
int				add_redirection_to_command(t_parsing *data, int type);
int				type_to_oflags(int type);
t_redirection	*init_redirection(t_parsing *data, int type, int o_flags);
t_command		*init_operator(t_parsing *data, t_command *left_command);
int				token_to_operator_type(t_token *token);
int				check_redirection(t_redirection	*redirection);
int				open_redirections(t_command *command);
int				ft_open_redirect(t_redirection *redirection);
int				parse_redirection(t_redirection *redirection);
int				open_file(t_redirection *redirection);
int				args_number(t_token *token);
int				redirections_number(t_token *token);
t_command		*create_command(t_parsing *data);
int				weight_by_type(int type);
int				next_operator_weight(t_parsing *data);
t_command		*last_command(t_command *current);
t_redirection	*init_others_redirection(t_parsing *data, int type, int o_flags);
void			redirect_add_back(t_redirection **lst, t_redirection *redirect);

t_redirection	*init_here_doc(t_parsing *data);
int	open_here_doc(t_redirection *redirection);

#endif