/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:05:54 by mdembele          #+#    #+#             */
/*   Updated: 2024/09/13 03:11:27 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"
#include "built_in.h"

static int	cd_oldpwd(void);

int	cd(char **args)
{
	char	*actual_path;
	char	*dir;

	if (ft_strlen_2d(args) > 2)
		return (cd_error("too many arguments", false));
	if (args[1] != NULL && ft_strcmp(args[1], "-") == 0)
		return (cd_oldpwd());
	actual_path = ft_getenv("PWD");
	if (args[1] != NULL)
		dir = args[1];
	else
	{
		dir = ft_getenv("HOME");
		if (dir == NULL)
			return (cd_error("HOME not set", false));
	}
	if (chdir(dir) == -1)
		return (cd_error(NULL, true));
	if (update_pwd(actual_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

static int	cd_oldpwd(void)
{
	char	*actual_path;
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (oldpwd == NULL)
		return (cd_error("OLDPWD not set", false));
	actual_path = ft_getenv("PWD");
	if (chdir(oldpwd) == -1)
		return (cd_error(NULL, true));
	ft_putendl_fd(oldpwd, STDERR_FILENO);
	if (update_pwd(actual_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

int	cd_error(char *err, bool erno)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (erno == true)
		perror(err);
	else if (err != NULL)
		ft_putendl_fd(err, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	update_pwd(char *old_pwd)
{
	int		status;
	char	*pwd;

	status = EXIT_SUCCESS;
	if (create_and_add_env_var("OLDPWD", old_pwd) == EXIT_FAILURE)
		status = EXIT_FAILURE;
	pwd = ft_getcwd();
	if (pwd == NULL)
		status = EXIT_FAILURE;
	if (create_and_add_env_var("PWD", pwd) == EXIT_FAILURE)
		status = EXIT_FAILURE;
	return (status);
}
