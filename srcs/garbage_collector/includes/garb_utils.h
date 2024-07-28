#ifndef GARB_UTILS_H
# define GARB_UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

# include "../../../includes/structs.h"

# define E1 "Error: use ft_malloc before any other garbage_collector functions"
# define E2 "Error: can't use an garbage function after using destroy_garbage()"
# define E3 "Error: use of ft_free on an address non allocated by ft_malloc()"
# define MALLOC_FAILED "Error: garbage_collector: malloc failed"
# define WRITE_ERROR "Error: garbage_collector: write function failed"

void		*ft_malloc(unsigned long size);
void		ft_free(void **address);
void		destroy_garbage(t_garbage *garb);
t_garb_node	*find_in_garbage(void *address, t_garbage *garbage);
int			new_garb_node(void *adress, t_garbage *garbage);
void		destroy_garbage_node(t_garb_node *node);
t_garbage	*init_garbage(void);
int	init_static(t_garbage **_static, void **arg);

#endif