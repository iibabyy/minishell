#include "garb_utils.h"

t_garb_node	*find_by_address(void *address, t_garbage *garbage)
{
	t_garb_node	*node;

	node = garbage->first;
	while (node != NULL)
	{
		if (node->address == address)
			break ;
		node = node->next;
	}
	return (node);
}

t_garb_node	*find_before_node(t_garb_node *node, t_garbage *garbage)
{
	t_garb_node	*before_node;

	if (node == garbage->first)
		return (NULL);
	before_node = garbage->first;
	while (before_node != NULL)
	{
		if (before_node->next == node)
			return (before_node);
		before_node = before_node->next;
	}
	return (NULL);
}
