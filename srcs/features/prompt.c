/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:42:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 00:41:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

char	*minishell_prompt()
{
	char	*prompt = NULL;
	char	*pwd = NULL;

	if (pwd == NULL)
		pwd = ft_getenv("PWD");
	if (pwd == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = add_arrow();
	if (prompt == NULL)
		return (ft_strdup(MINISHELL_PROMPT));
	prompt = add_dir_name(prompt);
	prompt = add_git_head(prompt);
	prompt = ft_re_strjoin(prompt, "\001\033[0m\002");
	if (prompt == NULL || *prompt == '\0')
		return (ft_free(prompt), ft_strdup(MINISHELL_PROMPT));
	return (prompt);
}

char	*add_dir_name(char *prompt)
{
	char	*dir;
	char	*temp;

	temp = ft_getcwd();
	if (temp == NULL || ft_strchr(temp, '/') == NULL)
	{
		dir = ft_strjoin(prompt, "minishell ");
		if (dir == NULL)
			return (prompt);
		return (ft_free(prompt), dir);
	}
	if (ft_getenv("HOME") != NULL && ft_strcmp(ft_getenv("HOME"), temp) == 0)
		dir = ft_strdup("~ ");
	else if (*(ft_strrchr(temp, '/') + 1) == '\0')
		dir = ft_strdup("/ ");
	else
		dir = ft_strjoin(ft_strrchr(temp, '/') + 1, " ");
	if (dir == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, dir);
	ft_free(dir);
	if (temp == NULL)
		return (prompt);
	return (ft_free(prompt), temp);
}

char	*add_git_head(char *prompt)
{
	char	*git;
	char	*temp;
	
	temp = git_head();
	if (temp == NULL)
		return (prompt);
	git = multi_strjoin(3, "\001\033[34;1m\002git:(\001\033[31;1m\002",
			temp, "\001\033[34;1m\002) ");
	ft_free(temp);
	if (git == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, git);
	ft_free(git);
	if (temp == NULL)
		return (prompt);
	temp = add_git_delay(temp);
	return (ft_free(prompt), temp);
}

char	*add_git_delay(char *prompt)
{
	char	*head;

	head = git_head();
	if (head == NULL)
		return (NULL);
	if (is_delayed(head) != true)
		return (ft_free(head), prompt);
	ft_free(head);
	head = ft_strjoin(prompt, "\001\033[33;1m\002✗ ");
	if (head == NULL)
		return (prompt);
	return (ft_free(prompt), head);
}

char	*add_arrow(void)
{
	char	*color;
	char	*arrow;

	if (get_code(0, false) == EXIT_SUCCESS)
		color = "\001\033[32;5m\002";
	else
		color = "\001\033[31;5m\002";
	arrow = ft_strjoin(color, "➜  \001\033[0m\033[36;1m\002");
	if (arrow == NULL)
		return (NULL);
	return (arrow);
}
