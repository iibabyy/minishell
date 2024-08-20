/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:15:31 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/20 22:16:35 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../../includes/minishell.h"

# define QUOTES_PROMPT "quotes> "
# define PARENTHESIS_PROMPT ""

t_token	*input_to_tokens(char *input);
int		word_to_token(char **input, int start, int *end, t_token **tokens);
int		meta_to_token(char **input, int *index, t_token **tokens);
bool	is_meta_char(char *input, int index);
bool	is_operator(char *input, int index);
bool	is_redirection(char c);
bool	is_quotes(char c);
int		metachar_size(char **input, int start);
int		char_type(char *str, int index);
t_token	*init_token(char **input, int start);
char	*env_to_string(char	*str, int *i);
char	*replace_env_vars(char *input);
int		quotes_size(char **input, int start, char eof);
int		new_word_token(t_token **tokens, char *word);
int		new_parenthesis(char **input, int start, int *end, t_token **token);
int		parenthesis_size(char **input, int start);
char	**replace_dollars(char *input);
char    *split_env_var(char *env);

#endif