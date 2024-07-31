#include "parsing.h"

t_here_doc	*init_here_doc(t_parsing *data)
{
	t_here_doc	*here_doc;

	here_doc = ft_malloc(sizeof(t_here_doc));
	if (here_doc == NULL)
		return (print_err("init_here_doc: ft_calloc() failed", true), NULL);
	if (pipe(here_doc->pipe) == -1)
		return (print_err("init_here_doc: pipe() failed", true),
				parse_err(NULL, NULL), NULL);
	here_doc->token = data->curr_token;
	here_doc->command = data->command;
	data->curr_token = data->curr_token->next;
	here_doc->end_of_file = data->curr_token;
	return (here_doc);
}

// t_here_doc	*last_here_doc(t_parsing *data)
// {
// 	t_here_doc	*here_doc;

// 	if (data->here_doc == NULL)
// 		return (NULL);
// 	here_doc = data->here_doc;
// 	while (here_doc->next != NULL)
// 	{
// 		here_doc = here_doc->next;
// 	}
// 	return (here_doc);
// }
