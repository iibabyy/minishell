#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

#include "../../includes/minishell.h"

t_command	*init_command(void);
int			add_words_to_command(t_command *command, t_token **token);
int			add_redirections_to_command(t_command *command, t_token **token);
int			add_output(t_command *command, t_token **token);
int			add_output_append(t_command *command, t_token **token);
int			add_input(t_command *command, t_token **token);
int			add_here_doc(t_command *command, t_token **token);

#endif