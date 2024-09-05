/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:25:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/05 17:51:52 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURES_H
# define FEATURES_H

# include "../../includes/minishell.h"

# define MSHRC ".mshrc"
# define MAX_ALIAS 128
# define HISTORY_FILE "/tmp/.history"
# define ALIAS_USAGE "alias: usage: abc=xyz"

char	***get_alias(char ***init_alias);
int		check_if_alias(t_command *command, char ***aliases);
int		init_aliases(void);
char	***search_aliases(int fd);
char	**line_to_alias(char *line);
void	clear_3d_array(char ***alias, int end);
char	***get_alias(char ***init_alias);
char	**add_alias(char **array, char *line, int start);
char	**insert_alias(char **command, char **alias);
char	*get_last_history(char *str, bool set);
void	add_and_save(char *str);

#endif