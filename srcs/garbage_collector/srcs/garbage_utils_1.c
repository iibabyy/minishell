#include "garb_utils.h"

t_garb_node	*find_in_garbage(void *address, t_garbage *garbage)
{
	t_garb_node	*garb_node;

	garb_node = garbage->first;
	while (garb_node != NULL)
	{
		if (garb_node->address == address)
			return (garb_node);
		garb_node = garb_node->next;
	}
	return (NULL);
}

t_garbage	*init_garbage(void)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage) * 1);
	if (garbage == NULL)
		return (NULL);
	garbage->first = NULL;
	ft_free(garbage);
	destroy_garbage(garbage);
	return (garbage);
}

void	destroy_garbage_node(t_garb_node *node_to_destroy)
{
	free(node_to_destroy->address);
	free(node_to_destroy);
}

int	new_garb_node(void *address, t_garbage *garbage)
{
	t_garb_node	*new_node;

	new_node = malloc(sizeof(t_garb_node) * 1);
	if (new_node == NULL)
		return (EXIT_FAILURE);
	new_node->address = address;
	new_node->next = garbage->first;
	garbage->first = new_node;
	return (EXIT_SUCCESS);
}
