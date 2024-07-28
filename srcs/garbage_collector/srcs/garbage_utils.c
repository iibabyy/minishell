#include "../includes/garb_utils.h"

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
		return (free(garbage), perror(MALLOC_FAILED), NULL);
	garbage->first = NULL;
	ft_free((void **)&garbage);
	destroy_garbage(garbage);
	return (garbage);
}

void	destroy_garbage_node(t_garb_node *node)
{
	free(node->address);
	free(node);
}

int	new_garb_node(void *adress, t_garbage *garbage)
{
	t_garb_node	*new_node;

	new_node = malloc(sizeof(t_garb_node) * 1);
	if (new_node == NULL)
		return (perror(MALLOC_FAILED), EXIT_FAILURE);
	new_node->address = adress;
	new_node->next = garbage->first;
	garbage->first = new_node;
	return (EXIT_SUCCESS);
}

void	print_err(char *error)
{
	int	i;

	if (error == NULL)
		return ;
	i = -1;
	while (error[++i])
	{
		if (write(STDERR_FILENO, &error[i], 1) < 0)
			return (print_err(WRITE_ERROR));
	}
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return (print_err(WRITE_ERROR));
}
