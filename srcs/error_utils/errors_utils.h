/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:38 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 03:05:04 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_UTILS_H
# define ERRORS_UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../../includes/garbage_collector.h"
# include "../../includes/libft.h"

# define ERROR_LOG_FILE ".error_log"

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

#endif