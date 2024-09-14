/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:17:53 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:36:34 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "structs.h"

int		errcode(int errcode, bool setter);
void	free_all(void);
void	print_err(char *err, bool erno);
void	print_err_and_exit(char *err, int status, bool erno);
void	parse_err(char *error, char *token);
void	destroy_commands(t_command *command);
void	destroy_tokens(t_token *tokens);
void	destroy_here_docs(t_here_doc *here_doc);
void	destroy_redirections(t_redirection *redirection);
void	destroy_parsing(t_parsing *data);
void	init_error_log(void);
void	error_log(char *error, bool erno);
void	malloc_failed(char *function);
void	free_and_exit(int status);
char	*replace_newline(char *str);

#endif