/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:10:53 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/14 20:00:15 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_dup2(int *fd, int fd2);

int	open_here_doc(t_redirection *redirection)
{
	t_here_doc	*here_doc;
	char		*input;

	if (redirection->type != HERE_DOC)
		return (parse_err(TOKEN_ERR, redirection->token->content),
			EXIT_FAILURE);
	here_doc = redirection->here_doc;
	input = get_input(here_doc->end_of_file->content, HEREDOC_PROMPT, false);
	if (g_signal != 0)
		return (ft_free(input), EXIT_FAILURE);
	input = replace_env_vars(input);
	if (input == NULL)
		return (EXIT_FAILURE);
	here_doc->input = input;
	return (EXIT_SUCCESS);
}

static bool	is_limiter(char *input, char *limiter)
{
	size_t	input_len;

	input_len = ft_strlen(input);
	if (input_len < 1)
	{
		return (false);
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

char	*check_here_doc_input(char *input)
{
	if (input == NULL)
		return (ft_strdup(""));
	return (input);
}

char	*get_input(char *end_of_file, char *prompt, bool quotes)
{
	char	*input;
	char	*input_join;

	input_join = NULL;
	while (1)
	{
		input = readline(prompt);
		if (input == NULL || g_signal != 0)
			return (check_heredoc_sig(input_join, end_of_file));
		if (quotes == true || input_join != NULL)
		{
			input_join = ft_re_strjoin(input_join, "\n");
			if (input_join == NULL)
				return (NULL);
		}
		if (quotes == false && is_limiter(input, end_of_file) == true)
			return (free(input), check_here_doc_input(input_join));
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
		return (malloc_failed("init_here_doc"), NULL);
	redirection->here_doc->token = data->curr_token;
	redirection->type = HERE_DOC;
	redirection->command = data->command;
	data->curr_token = data->curr_token->next;
	if (data->curr_token == NULL)
		return (parse_err(TOKEN_ERR, "newline"), ft_free(redirection), NULL);
	redirection->here_doc->end_of_file = data->curr_token;
	return (redirection);
}
