#ifndef ERRORS_UTILS_H
# define ERRORS_UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include "../../includes/garbage_collector.h"
# include "../../includes/libft.h"

void	free_all(t_data *data);
void	print_err(char *err, bool errno);
void	print_err_and_exit(char *err, int status, bool errno);
void	parse_err(char *error, char *token);
void	destroy_commands(t_command *command);
void	destroy_tokens(t_token *tokens);
void	destroy_here_docs(t_here_doc *here_doc);
void	destroy_redirections(t_redirection *redirection);
void	destroy_parsing(t_parsing *data);

#endif