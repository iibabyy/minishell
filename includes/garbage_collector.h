#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

void	destroy_garbage(t_garbage *garbage);
void	ft_free(void *address);
void	print_err_and_exit(char *err, int status, bool errno);

#endif