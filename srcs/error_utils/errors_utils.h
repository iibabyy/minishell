/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:38 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:57:20 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_UTILS_H
# define ERRORS_UTILS_H

# include "../../includes/minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

void	ft_close(int *fd);
void	free_all(void);
void	print_err(char *err, bool erno);
void	print_err_and_exit(char *err, int status, bool erno);
void	parse_err(char *error, char *token);
void	destroy_commands(t_command *command);
void	destroy_tokens(t_token *tokens);
void	destroy_here_docs(t_here_doc *here_doc);
void	destroy_redirections(t_redirection *redirection);
void	destroy_parsing(t_parsing *data);
void	error_log(char *error, bool erno);
void	built_in_error(char *function, char *error, bool erno);
char	*replace_newline(char *str);

#endif