#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <stdbool.h>
# include "garbage_collector.h"
# include "libft.h"

void	free_all(struct s_data *data);
void	free_and_exit(char *err, int status, struct s_data *data, bool errno);
void	print_err(char *err, bool errno);
void	print_err_and_exit(char *err, int status, bool errno);

#endif