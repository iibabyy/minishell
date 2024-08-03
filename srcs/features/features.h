#ifndef FEATURES_H
# define FEATURES_H

#include "../../includes/minishell.h"

# define MSHRC "/home/idrissa/42/projects/minishell/.mshrc"
# define MAX_ALIAS 128

char	***get_alias(char ***init_alias);
int	check_if_alias(char **command, char ***aliases);
int	init_aliases();
char ***search_aliases(int fd);
char	**line_to_alias(char *line);
void	clear_3d_array(char ***alias, int end);
char	***get_alias(char ***init_alias);
char	**add_alias(char **array, char *line, int start);

#endif