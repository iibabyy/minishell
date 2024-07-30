#include "parsing_utils.h"

t_here_doc	*init_here_doc(t_parsing *data)
{
	t_here_doc	*here_doc;

	here_doc = ft_calloc(1, sizeof(t_here_doc));
	if (here_doc == NULL)
		return (print_err("init_here_doc: ft_calloc() function failed",
				true), NULL);
	if (pipe(here_doc->pipe) == -1)
		return (print_err("init_here_doc: pipe() function failed", true),
				parse_err(NULL, data), NULL);
	here_doc->token = data->curr_token;
	here_doc->command = data->curr_command;
	data->curr_token = data->curr_token->next;
	here_doc->end_of_file = data->curr_token->content;
}

t_here_doc	*last_here_doc(t_parsing *data)
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
