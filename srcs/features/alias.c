#include "features.h"

int	replace_aliases(t_command *last_command)
{
	static char	***alias;

	if (alias == NULL)
		alias = get_alias(NULL);
	if (last_command == NULL)
		return (EXIT_SUCCESS);
	if (check_if_alias(&last_command->command[0], alias) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (replace_aliases(last_command->left) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (replace_aliases(last_command->right) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_if_alias(char **command, char ***aliases)
{
	char	*alias;
	int		i;

	i = -1;
	while (aliases[++i])
	{
		if (ft_strcmp(aliases[i][0], *command) == 0)
		{
			alias = ft_strdup(aliases[i][1]);
			if (alias == NULL)
				return (EXIT_FAILURE);
			*command = alias;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

int	init_aliases()
{
	char	***aliases;
	int	mshrc_fd;

	mshrc_fd = open(MSHRC, O_RDONLY);
	if (mshrc_fd == -1)
		return (EXIT_FAILURE);
	aliases = search_aliases(mshrc_fd);
	if (aliases == NULL)
		return (EXIT_FAILURE);
	get_alias(aliases);
	return (EXIT_SUCCESS);
}

char ***search_aliases(int fd)
{
	char	***aliases;
	char	*line;
	int		i;

	i = 0;
	aliases = ft_calloc(MAX_ALIAS, sizeof(char **));
	do
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "alias ", 6) == 0)
		{
			aliases[i] = line_to_alias(line);
			if (aliases[i] != NULL)
				return (clear_3d_array(aliases, i), NULL);
			++i;
		}
		ft_free(line);
	}	while (line != NULL && i < MAX_ALIAS);
	aliases[i] = NULL;
	if (aliases[0] == NULL)
		return (ft_free(aliases), NULL);
	return (aliases);
}

char	**line_to_alias(char *line)
{
	char	**alias;
	int		i;
	int		start;

	i = 6;
	while (line[i] == ' ' && line[i] != '\0')
		++i;
	start = i;
	while (line[i] != '=')
		if (ft_isalpha(line[i++]) == false)
			return (NULL);
	alias = ft_malloc(sizeof(char *) * 2);
	if (alias == NULL)
		return (NULL);
	alias[0] = ft_substr(line, start, i - start);
	if (alias[0] == NULL)
		return (ft_free(alias), NULL);
	start = ++i;
	while (ft_isalpha(line[i]))
		++i;
	alias[1] = ft_substr(line, start, i - start);
	if (alias[1] == NULL)
		return (ft_free(alias[0]), ft_free(alias), NULL);
	return (alias);
}
