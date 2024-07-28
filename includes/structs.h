#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	void	*infos;
}	t_data;

//	Garbage Collector

typedef struct s_garb_node
{
	void				*address;
	struct s_garb_node	*next;
}	t_garb_node;

typedef struct s_garbage
{
	t_garb_node	*first;
}	t_garbage;

//	Lexing
# define META_CHARS ""
# define WORD 1			//	commands, arguments, etc...
# define OPERATOR 2			//	|, ||, &&, () and newlines.
# define REDIRECTION 3		//	<, <<, >, >>.
# define STRING 4
typedef struct s_token
{
	int		type;
	char	*content;
	t_token	*next;
}	t_token;

#endif