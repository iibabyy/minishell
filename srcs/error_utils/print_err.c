/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:52 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 17:14:03 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

void	print_err(char *err, bool erno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (erno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd(err, STDERR_FILENO);
	}
}

void	parse_err(char *error, char *token)
{
	if (token == NULL && error != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	else if (token != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
}

void	error_log(char *error, bool erno)
{
	static int	error_num = 0;
	int			error_log_fd;

	error_log_fd = open(ERROR_LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (error_log_fd == -1)
		return ;
	if (++error_num != 1)
		ft_putstr_fd("\n\n", error_log_fd);
	ft_putnbr_fd(error_num, error_log_fd);
	ft_putstr_fd(".\n", error_log_fd);
	if (erno == true)
	{
		ft_putstr_fd(error, error_log_fd);
		ft_putendl_fd(strerror(errno), error_log_fd);
	}
	if (error != NULL)
		ft_putendl_fd(error, error_log_fd);
	ft_close_fd(&error_log_fd);
}

void	init_error_log(void)
{
	int	fd;

	unlink(ERROR_LOG_FILE);
	fd = open(ERROR_LOG_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return ;
	write (fd, "\0", 1);
	close(fd);
}
