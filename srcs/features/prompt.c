/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:42:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/05 21:27:52 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

//\033[0;33m✗

char	*minishell_prompt()
{
	static char	*prompt = NULL;
	static char	*pwd = NULL;

	if (pwd == NULL)
		pwd = ft_getenv("PWD");
	if (pwd == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	if (prompt != NULL && ft_strcmp(pwd, ft_getenv("PWD")) == 0)
		return (prompt);
	prompt = ft_strdup("\033[0;32m➜  \033[0;36m\033[1mminishell ");
	if (prompt == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = add_git_head(prompt);
	prompt = ft_re_strjoin(prompt, "\033[0;33m✗ \033[0m");
	if (prompt == NULL || *prompt == '\0')
		return (ft_free(prompt), ft_strdup(MINISHELL_PROMPT));
	printf("prompt: [%s]\n", prompt);
	return (prompt);
}

char	*add_git_head(char *prompt)
{
	char	*git;
	char	*temp;
	int		fd;
	
	if (access("./.git/HEAD", F_OK | R_OK) != 0)
		return (prompt);
	fd = open("./.git/HEAD", O_RDONLY);
	if (fd == -1)
		return (prompt);
	temp = get_next_line(fd);
	if (ft_strrchr(temp, '\n') != NULL)
		*ft_strrchr(temp, '\n') = '\0';
	if (temp == NULL)
		return (prompt);
	printf("temp: [%s]\n", temp);
	if (ft_strrchr(temp, '/') == NULL)
		return (ft_free(temp), prompt);
	git = multi_strjoin(3, "\033[0;34m\033[1mgit:(\033[0;31m\033[1m",
			ft_strrchr(temp, '/') + 1, "\033[0;34m\033[1m) ");
	ft_free(temp);
	if (git == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, git);
	if (temp == NULL)
		return (ft_free(git), prompt);
	return (ft_free(prompt), ft_free(git), temp);
}
