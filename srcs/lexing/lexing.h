#ifndef LEXING_H
# define LEXING_H

# include <stdbool.h>

# include "../../includes/minishell.h"

t_token	*input_to_tokens(char *input);
int		word_to_token(char *input, int start, int end, t_token **tokens);
int		meta_to_token(char *input, int index, t_token **tokens);
bool	is_meta_char(char *input, int index);
bool	is_operator(char *input, int index);
bool	is_redirection(char c);
bool	is_quotes(char c);
int		metachar_size(char *input, int start);
int		char_type(char *str, int index);
t_token	*init_token(char *input, int start);
char	*env_to_string(char	*str, int *i);
char	*replace_env_vars(char *input);

#endif