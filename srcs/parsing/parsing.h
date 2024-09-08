/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:10:05 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 03:52:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"

/*  Priorities	*/

# define SUB_SH_WEIGHT 0
# define AND_WEIGHT 1
# define OR_WEIGHT 1
# define PIPE_WEIGHT 2
# define HEREDOC_PROMPT "heredoc> "

t_command		*token_to_ast(t_parsing *data, int weight);
t_command		*create_ast(t_parsing *data, t_command *left, int weight);
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
int				open_file(t_redirection *redirection);
int				args_number(t_token *token);
int				redirections_number(t_token *token);
t_command		*create_command(t_parsing *data);
int				weight_by_type(int type);
int				next_operator_weight(t_parsing *data);
t_command		*last_command(t_command *current);
t_redirection	*init_others_redirection(t_parsing *data, int type, int oflags);
void			redirect_add_back(t_redirection **lst, t_redirection *redirect);
bool			is_standart_fd(int fd);
t_redirection	*init_here_doc(t_parsing *data);
int				open_here_doc(t_redirection *redirection);
char			*check_heredoc_sig(char *input, char *eof);
void			ft_close(int *fd);

#endif