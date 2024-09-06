/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:42:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 02:42:57 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

void	close_and_re(int fd);

char	*minishell_prompt()
{
	char	*prompt = NULL;
	char	*pwd = NULL;

	if (pwd == NULL)
		pwd = ft_getenv("PWD");
	if (pwd == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = ft_strdup("\001\033[0;32m\002➜  \001\033[0;36m\033[1m\002");
	if (prompt == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = add_dir_name(prompt);
	prompt = add_git_head(prompt);
	prompt = ft_re_strjoin(prompt, "\001\033[33;1m\002 ✗\001\033[0m\002 ");
	if (prompt == NULL || *prompt == '\0')
		return (ft_free(prompt), ft_strdup(MINISHELL_PROMPT));
	return (prompt);
}

char	*add_dir_name(char *prompt)
{
	char	*dir;
	char	*temp;

	temp = ft_getenv("PWD");
	if (temp == NULL || ft_strrchr(temp, '/') == NULL)
	{
		dir = ft_strjoin(prompt, "minishell");
		if (dir == NULL)
			return (prompt);
		return (ft_free(prompt), ft_free(temp), dir);
	}
	dir = ft_strrchr(temp, '/') + 1;
	if (*dir == '\0')
		dir = "/";
	dir = ft_strjoin(prompt, dir);
	if (dir == NULL)
		return (prompt);
	return (ft_free(prompt), dir);
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
	close_and_re(fd);
	if (ft_strrchr(temp, '\n') != NULL)
		*ft_strrchr(temp, '\n') = '\0';
	if (temp == NULL)
		return (prompt);
	if (ft_strrchr(temp, '/') == NULL)
		return (ft_free(temp), prompt);
	git = multi_strjoin(3, " \001\033[0;34m\033[1m\002git:(\001\033[0;31m\033[1m\002",
			ft_strrchr(temp, '/') + 1, "\001\033[0;34m\033[1m\002)");
	ft_free(temp);
	if (git == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, git);
	if (temp == NULL)
		return (ft_free(git), prompt);
	return (ft_free(prompt), ft_free(git), temp);
}

void	close_and_re(int fd)
{
	close(fd);
	lseek(fd, 0, SEEK_SET);
}
