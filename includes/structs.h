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
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

//	Parsing

# define COMMAND 1
# define PIPE 2
# define OR 4
# define AND 3
# define SUB_SHELL 4
# define TOKEN_ERR "syntaxe error near token "

typedef struct s_command
{
	int					type;
	char				**command;
	int					infile;
	int					outfile;
	struct s_command	*left;
	struct s_command	*right;
}	t_command;

typedef struct s_here_doc
{
	int					pipe[2];
	char				*end_of_file;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_parsing
{
	t_command	*command;
	t_command	*curr_command;
	t_token		*token;
	t_token		*curr_token;
	t_here_doc	*here_doc;
}	t_parsing;

#endif