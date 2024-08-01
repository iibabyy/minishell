#include "parsing.h"

/*
Fork() ? :	(No)
bash can see next syntaxes errors before executing pipe.
Is it because he just save all the here_docs, then check the errors,
and then executing here_doc ?
or because he just fork() the here_doc and continue the parsing ?
(and wait() for the process(es) to finish the here_docs)

Instead :

Save and open ? :

Saving all the base redirections '<', '>' and '>>' in a chained list,
and all the Here_docs in an other chained list.
Add the corresponding command, files,
and token ('<', '<<', '>', '>>') into the struct.
Don't do the redirections parsing now (for example '<<<<<' must not arrest us !)
Then, when we finish to parse the input,
start parsing and opening all the redirections:
starting with all the here_doc,
then all the base redirections.
Like that, we can reproduce the way bash handle redirections errors,
mainly the here_docs errors.
*/

int	open_here_doc(t_redirection *redirection)
{
	t_here_doc	*here_doc;
	char		*input;

	if (redirection->type != HERE_DOC)
		return (parse_err(TOKEN_ERR, redirection->token->content),
				EXIT_FAILURE);
	here_doc = redirection->here_doc;
	input = get_input(here_doc->end_of_file->content, true);
	if (input == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd(input, redirection->here_doc->pipe[1]);
	print_file(redirection->here_doc->pipe[1]);
	ft_free(input);
	return (EXIT_SUCCESS);
}

static bool	is_limiter(char *input, char *limiter)
{
	size_t	input_len;

	input_len = ft_strlen(input);
	if (input_len <= 1)
	{
		return (false);
	}
	if (input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}
	if (ft_strcmp(input, limiter) == 0)
	{
		return (true);
	}
	else
	{
		input[input_len - 1] = '\n';
		return (false);
	}
}

char	*get_input(char *end_of_file, bool quotes)
{
	char	*input;
	char	*input_join;

	input_join = ft_strdup("\n");
	if (input_join == NULL)
		return (print_err("get_here_doc(): ft_strdup() failed", false), NULL);
	while (1)
	{
		
		input = readline("> ");
		if (input == NULL)
			return (print_err("get_here_doc(): readline() failed", false),
				NULL);
		if (quotes == false && is_limiter(input, end_of_file) == 0)
			return (free(input), input_join);
		input_join = multi_re_strjoin(3, input_join, input, "\n");
		if (input_join == NULL)
			return (print_err("get_here_doc(): ft_re_strjoin() failed", false),
				NULL);
		if (quotes == true && ft_strchr(input, end_of_file[0]) != NULL)
			return (free(input), input_join);
		free(input);
	}
	return (input_join);
}

t_redirection	*init_here_doc(t_parsing *data)
{
	t_redirection	*redirection;

	redirection = ft_malloc(sizeof(t_redirection) * 1);
	if (redirection == NULL)
		return (print_err("init_here_doc(): ft_malloc() function failed",
				false), NULL);
	ft_memset(redirection, 0, sizeof(t_redirection));
	redirection->here_doc = ft_malloc(sizeof(t_here_doc));
	if (redirection->here_doc == NULL)
		return (print_err("init_here_doc: ft_malloc() failed", true), NULL);
	if (pipe(redirection->here_doc->pipe) == -1)
		return (print_err("init_here_doc: pipe() failed", true),
				parse_err(NULL, NULL), NULL);
	redirection->here_doc->token = data->curr_token;
	printf("%p\n", &data->curr_token);
	redirection->type = HERE_DOC;
	redirection->here_doc->command = data->command;
	data->curr_token = data->curr_token->next;
	redirection->here_doc->end_of_file = data->curr_token;
	return (redirection);
}
