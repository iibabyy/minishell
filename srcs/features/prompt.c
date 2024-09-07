/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:42:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/07 21:49:53 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

//	

char	*minishell_prompt()
{
	char	*prompt = NULL;
	char	*pwd = NULL;

	if (pwd == NULL)
		pwd = ft_getenv("PWD");
	if (pwd == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = ft_strdup("\001\033[32;5m\002➜  \033[0m\001\033[36;1m\002");
	if (prompt == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = add_dir_name(prompt);
	prompt = add_git_head(prompt);
	prompt = ft_re_strjoin(prompt, "\001\033[0m\002 ");
	if (prompt == NULL || *prompt == '\0')
		return (ft_free(prompt), ft_strdup(MINISHELL_PROMPT));
	return (prompt);
}

char	*add_dir_name(char *prompt)
{
	char	*dir;
	char	*temp;

	temp = ft_getcwd();
	if (temp == NULL || ft_strrchr(temp, '/') == NULL)
	{
		dir = ft_strjoin(prompt, "minishell ");
		if (dir == NULL)
			return (prompt);
		return (ft_free(prompt), ft_free(temp), dir);
	}
	if (ft_getenv("HOME") != NULL && ft_strcmp(ft_getenv("HOME"), temp) == 0)
	{
		dir = ft_strjoin(prompt, "~");
		if (dir == NULL)
			return (prompt);
		return (ft_free(temp), ft_free(prompt), dir);
	}
	dir = ft_strrchr(temp, '/') + 1;
	if (*dir == '\0')
		dir = "/";
	dir = multi_strjoin(3, prompt, dir, " ");
	if (dir == NULL)
		return (prompt);
	return (ft_free(prompt), dir);
}

char	*add_git_head(char *prompt)
{
	char	*git;
	char	*temp;
	
	temp = git_line("HEAD");
	if (temp == NULL)
		return (prompt);
	if (ft_strrchr(temp, '\n') != NULL)
		*ft_strrchr(temp, '\n') = '\0';
	if (ft_strrchr(temp, '/') == NULL)
		return (ft_free(temp), prompt);
	git = multi_strjoin(3, "\001\033[34;1m\002git:(\001\033[31;1m\002",
			ft_strrchr(temp, '/') + 1, "\001\033[34;1m\002) ");
	if (git == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, git);
	if (temp == NULL)
		return (ft_free(git), prompt);
	temp = add_git_delay(temp);
	return (ft_free(prompt), ft_free(git), temp);
}

char	*add_git_delay(char *prompt)
{
	char	*git;
	char	*temp;
	
	git = git_line("refs/heads/main");
	if (ft_strrchr(git, '\n') != NULL)
		*ft_strrchr(git, '\n') = '\0';
	temp = git_line("refs/remotes/origin/main");
	if (temp == NULL || git == NULL)
		return (prompt);
	if (ft_strcmp(git, temp) == 0)
		return (prompt);
	(ft_free(git), ft_free(temp));
	git = ft_strjoin(prompt, "\001\033[33;1m\002✗");
	if (git == NULL)
		return (prompt);
	return (ft_free(prompt), git);
}

char	*git_line(char *git_file)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	path = ft_strdup(".git/");
	if (path == NULL)
		return (NULL);
	while (access(path, X_OK) != 0)
	{
		if (++i > 20)
			return (NULL);
		temp = path;
		path = ft_strjoin("../", path);
		ft_free(temp);
		if (path == NULL)
			return (NULL);
	}
	path = ft_strjoin(".git/", git_file);
	if (path == NULL)
		return (NULL);
	i = open(path, O_RDONLY);
	if (i == -1)
		return (ft_free(path), NULL);
	temp = get_next_line(i);
	close_and_re(i);
	return (ft_free(path), temp);
}
