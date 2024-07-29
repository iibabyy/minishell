#include "garb_utils.h"

static int	is_destroyed(bool setter, bool value);
static int	init_static(t_garbage **_static, void *arg);

/*	this function works like the real malloc function,
	it returns a pointers to an heap allocated zone.
	Make sure to use this function at least one time before the other functions.*/
void	*ft_malloc(unsigned long size)
{
	static t_garbage	*garbage = NULL;
	void				*ptr;

	if (is_destroyed(READER, false) == NOT_DEFINED)
		is_destroyed(SETTER, false);
	if (is_destroyed(READER, false) == true)
		return (NULL);
	if (garbage == NULL)
	{
		garbage = init_garbage();
		if (garbage == NULL)
			return (NULL);
	}
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	if (new_garb_node(ptr, garbage) == EXIT_FAILURE)
		return (free(ptr), NULL);
	return (ptr);
}

/*this function copy the real 'free( )' function.
You can use it on all addresses, 
whether they are allocated by the 'ft_malloc( )' function or not.*/
void	ft_free(void *address)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node_to_free;
	t_garb_node			*temp;

	if (address == NULL)
		return ;
	if (is_destroyed(READER, false) != false)
		return ;
	if (garbage == NULL)
		return ((void)init_static(&garbage, address));
	node_to_free = find_by_address(address, garbage);
	if (node_to_free == NULL)
		return ;
	temp = find_before_node(node_to_free, garbage);
	if (temp == NULL)
		garbage->first = node_to_free->next;
	else
		temp->next = node_to_free->next;
	destroy_garbage_node(node_to_free);
	return ;
}

/*this function free the garbage and all the addresses allocated
by 'ft_malloc( )' but not freed by 'ft_free( )'.
Use it with a NULL parameter.
Make sure to use this function at the very end, because the others functions are disabled after that.*/
void	destroy_garbage(t_garbage *garb)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node;
	t_garb_node			*temp;
	
	if (is_destroyed(READER, false) != false)
		return ;
	if (garbage == NULL)
	{
		init_static(&garbage, garb);
		return ;
	}
	node = garbage->first;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		destroy_garbage_node(temp);
	}
	free(garbage);
	is_destroyed(SETTER, true);
}

static int	init_static(t_garbage **_static, void *arg)
{
	if (arg == NULL)
		return (EXIT_FAILURE);
	*_static = (t_garbage *)arg;
	return (EXIT_SUCCESS);
}

static int	is_destroyed(bool setter, bool value)
{
	static int	is_destroy = NOT_DEFINED;

	if (setter == true)
		is_destroy = value;
	return (is_destroy);
}
