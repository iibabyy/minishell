#include "parsing_utils.h"

/*
Fork() ? :
bash can see next syntaxes errors before executing pipe.
Is it because he just save all the here_docs, then check the errors,
and then executing here_doc ?
or because he just fork() the here_doc and continue the parsing ?
(and wait() for the process(es) to finish the here_docs)


*/

int	add_here_doc(t_parsing	*data)
{
	t_here_doc	*here_doc;

	here_doc = init_t_here_doc(data);
}

t_here_doc	*init_t_here_doc(t_parsing *data)
{
	t_here_doc	*here_doc;

	here_doc = ft_calloc(1, sizeof(t_here_doc));
	if (here_doc == NULL)
		return (print_err("init_t_here_doc: ft_calloc() function failed",
				true), parse_err(NULL, data), NULL);
	if (data->here_doc == NULL)
		data->here_doc = here_doc;
	else
		find_last_here_doc(data)->next = here_doc;
	if (pipe(here_doc->pipe) == -1)
		return (print_err("init_t_here_doc: pipe() function failed", true),
				parse_err(NULL, data), NULL);
}

t_here_doc	*find_last_here_doc(t_parsing *data)
{
	t_here_doc	*here_doc;

	if (data->here_doc == NULL)
		return (NULL);
	here_doc = data->here_doc;
	while (here_doc->next != NULL)
	{
		here_doc = here_doc->next;
	}
	return (here_doc);
}
