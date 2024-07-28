#include "../includes/garb_utils.h"

static int	is_destroyed(bool seter, bool value);
int		init_static(t_garbage **_static, void **arg);
void	print_garbage_err(char *error);

//	this function works like the real malloc function, it returns a pointers to an heap allocated zone, of the size specified in parameter.
//	Make sure to use this function at least one time before the other garbage collector functions.
void	*ft_malloc(unsigned long size)
{
	static t_garbage	*garbage = NULL;
	void				*ptr;

	if (is_destroyed(false, false) == 3)
		is_destroyed(true, false);
	if (is_destroyed(false, false) != false)
		return (print_garbage_err(E2), NULL);
	if (garbage == NULL)
	{
		garbage = init_garbage();
		if (garbage == NULL)
			return (NULL);
	}
	ptr = malloc(size);
	if (ptr == NULL)
		return (perror(MALLOC_FAILED), NULL);
	if (new_garb_node(ptr, garbage) == EXIT_FAILURE)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

// this function copy the real 'free( )' function.
//You can use it on all addresses, whether they are allocated by the 'ft_malloc( )' function or not.
void	ft_free(void **address)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node_to_free;
	t_garb_node			*temp;

	if (address == NULL || *address == NULL)
		return ;
	if (is_destroyed(false, false) != false)
		return (print_garbage_err(E1));
	if (garbage == NULL)
		return ((void)init_static(&garbage, address));
	node_to_free = garbage->first;
	temp = NULL;
	while (node_to_free != NULL)
	{
		if (node_to_free->address == *address)
			break ;
		temp = node_to_free;
		node_to_free = node_to_free->next;
	}
	if (node_to_free == NULL && *address != NULL)
		return (free(*address));
	if (temp != NULL)
		temp->next = node_to_free->next;
	destroy_garbage_node(node_to_free);
	*address = NULL;
}

//this function free the garbage and all the addresses allocated by 'ft_malloc( )' but not freed by 'ft_free( )'.
//Use it with a NULL parameter.
//Make sure to use this function at the very end, because the others functions are disabled after that.
void	destroy_garbage(t_garbage *garb)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node;
	t_garb_node			*temp;

	if (is_destroyed(false, false) != false)
		return (print_garbage_err(E2));
	if (garbage == NULL)
	{
		init_static(&garbage, (void **)&garb);
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
	garbage = NULL;
	is_destroyed(true, true);
}

static int	is_destroyed(bool seter, bool value)
{
	static int	is_destroy = 3;

	if (seter == true)
		is_destroy = value;
	return (is_destroy);
}

void	print_garbage_err(char *error)
{
	int	i;

	if (error == NULL)
		return ;
	i = -1;
	while (error[++i])
	{
		if (write(STDERR_FILENO, &error[i], 1) < 0)
			return ;
	}
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return ;
}
