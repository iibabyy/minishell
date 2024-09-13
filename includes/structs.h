/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:38:12 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 03:38:13 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_data
{
	void					*infos;
}							t_data;

//	Garbage Collector

typedef struct s_garb_node
{
	void					*address;
	struct s_garb_node		*next;
	unsigned long			size;
	bool					locked;
}							t_garb_node;

typedef struct s_garbage
{
	t_garb_node				*first;
}							t_garbage;

//	Lexing

# define WORD 1 //	commands, arguments, etc...
# define OPERATOR 2 //	|, || and &&.
# define REDIRECTION 3 //	<, <<, >, >>.
# define PARENTHESIS 4 // (...)

typedef struct s_token
{
	int						type;
	char					*content;
	struct s_token			*next;
}							t_token;

//	Parsing

# define COMMAND 1
# define PIPE 2
# define AND 3
# define OR 4
# define SUB_SHELL 5

# define INPUT 1
# define APPEND_OUTPUT 2
# define OUTPUT 3
# define HERE_DOC 4

# define TOKEN_ERR "syntaxe error near unexpected token"

typedef struct s_parsing
{
	struct s_command		*command;
	t_token					*token;
	t_token					*curr_token;
	bool					error;
}							t_parsing;

typedef struct s_command
{
	char					**command;
	struct s_redirection	*redirections;
	struct s_command		*left;
	struct s_command		*right;
	struct s_command		*previous;
	int						pid;
	int						*pipe;
	int						infile;
	int						outfile;
	int						type;
	int						weight;
	bool					is_child;
	bool					sigint;
	bool					sigquit;
	bool					single;
}							t_command;

typedef struct s_here_doc
{
	int						pipe[2];
	char					*input;
	t_token					*end_of_file;
	t_token					*token;
	struct s_here_doc		*next;
}							t_here_doc;

typedef struct s_redirection
{
	t_token					*token;
	t_command				*command;
	t_token					*file;
	t_here_doc				*here_doc;
	int						type;
	int						o_flags;
	struct s_redirection	*next;
}							t_redirection;

//	built_in

typedef struct s_env_var
{
	char					*variable;
	char					*value;
	struct s_env_var		*next;
}							t_env_var;

typedef struct s_env
{
	t_env_var				*first;
}							t_env;

#endif