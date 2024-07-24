#include "garbage_collector.h"

t_garbage	*find_in_garbage(void *address, t_garbage *garbage)
{
	while (garbage != NULL)
	{
		if (garbage->address == address)
			return (garbage);
		garbage = garbage->next;
	}
	return (NULL);
}

t_garbage	*init_garbage(void)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage) * 1);
	if (garbage == NULL)
		print_err_and_exit("init_garbage: malloc failed", EXIT_FAILURE, true);
	ft_free(garbage);

}

void	destroy_garbage(t_garbage *garbage)
{
	static t_garbage	*garb;
	t_garbage			*node;
	t_garbage			*temp;

	if (garb == NULL)
	{
		garb = garbage;
		return ;
	}
	node = garb;
	while (node != NULL)
	{
		temp = node;
		free(node->address);
		node = node->next;
		free(temp);
	}
}
