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

# define WORD 1			//	commands, arguments, etc...
# define OPERATOR 2			//	|, ||, &&, () and newlines.
# define REDIRECTION 3		//	<, <<, >, >>.
# define STRING 4			// "abcde...", etc...

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
# define TOKEN_ERR "syntaxe error near unexpected token"

typedef struct s_command
{
	int					type;
	char				**command;
	int					infile;
	int					outfile;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*previous;
}	t_command;

typedef struct s_here_doc
{
	int					pipe[2];
	t_token				*end_of_file;
	t_command			*command;
	t_token				*token;
	struct s_here_doc	*next;
}	t_here_doc;

# define INPUT 1
# define APPEND_OUTPUT 2
# define OUTPUT 3
# define HERE_DOC 4

typedef struct s_redirection
{
	t_token					*token;
	t_command				*command;
	t_token					*file;
	t_here_doc				*here_doc;
	int						type;
	int						o_flags;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_parsing
{
	t_command		*command;
	t_token			*token;
	t_token			*curr_token;
	t_redirection	*redirection;
}	t_parsing;

#endif