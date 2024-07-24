#include "../../includes/garbage_collector.h"

void	*ft_malloc(size_t size)
{
	static t_garbage	*garbage;
	
	if (garbage == NULL)
		garbage = init_garbage();
}

void	ft_free(void *address)
{
	static t_garbage	*garbage;

	if (garbage == NULL)
	{
		garbage = address;
		return ;
	}
	find_in_garbage(garbage)->
}

