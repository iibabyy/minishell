/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:10:53 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/04 19:26:27 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void quit_heredoc(int sig)
{
	(void)sig;
	exit(0);
}
int	open_here_doc(t_redirection *redirection)
{
	t_here_doc	*here_doc;
	char		*input;
	int			*command_infile;

	if (redirection->type != HERE_DOC)
		return (parse_err(TOKEN_ERR, redirection->token->content),
			EXIT_FAILURE);
	command_infile = &redirection->command->infile;
	here_doc = redirection->here_doc;
	signal(SIGINT, &quit_heredoc);
	input = get_input(here_doc->end_of_file->content, HEREDOC_PROMPT, false);
	if (input == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd(input, here_doc->pipe[1]);
	ft_free(input);
	ft_close_fd(&here_doc->pipe[1]);
	if (is_standart_fd(*command_infile) == false)
		ft_close_fd(command_infile);
	*command_infile = here_doc->pipe[0];
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
	else if (input[input_len - 1] == '\0')
	{
		input[input_len - 1] = '\n';
	}
	return (false);
}

char	*get_input(char *end_of_file, char *prompt, bool quotes)
{
	char	*input;
	char	*input_join;

	input_join = NULL;
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			return (input_join);
		if (quotes == true || input_join != NULL)
		{
			input_join = ft_re_strjoin(input_join, "\n");
			if (input_join == NULL)
				return (NULL);
		}
		if (quotes == false && is_limiter(input, end_of_file) == true)
			return (free(input), input_join);
		input_join = ft_re_strjoin(input_join, input);
		if (input_join == NULL)
			return (NULL);
		if (quotes == true && ft_strchr(input, *end_of_file) != NULL)
			return (free(input), input_join);
		free(input);
	}
	return (input_join);
}

t_redirection	*init_here_doc(t_parsing *data)
{
	t_redirection	*redirection;

	if (data->curr_token == NULL)
		return (NULL);
	redirection = ft_calloc(1, sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->here_doc = ft_malloc(sizeof(t_here_doc));
	if (redirection->here_doc == NULL)
		return (NULL);
	if (pipe(redirection->here_doc->pipe) == -1)
		return (parse_err(NULL, NULL), NULL);
	redirection->here_doc->token = data->curr_token;
	redirection->type = HERE_DOC;
	redirection->command = data->command;
	data->curr_token = data->curr_token->next;
	redirection->here_doc->end_of_file = data->curr_token;
	return (redirection);
}

// char	*here_doc_subshell(char *input)
// {
// 	char	*subshell;

// 	subshell = ft_strdup(ft_strchr(input, '('));
// 	if (subshell == NULL)
// 		return (input);
// 	if (ft_strchr(subshell, ')')
// }
