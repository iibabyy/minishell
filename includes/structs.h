#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	void	*infos;
}	t_data;

typedef struct s_garb_node
{
	void				*address;
	struct s_garb_node	*next;
}	t_garb_node;

typedef struct s_garbage
{
	t_garb_node	*first;
}	t_garbage;

#endif