#ifndef ERROR_H
# define ERROR_H

#include "structs.h"

void	free_all(t_data *data);
void	free_and_exit(char *err, int status, t_data *data, bool errno);
void	print_err(char *err, bool errno);
void	print_err_and_exit(char *err, int status, bool errno);
void	parse_err(char *error, t_parsing *data);
void	destroy_commands(t_command *command);

#endif