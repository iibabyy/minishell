#include "features.h"

void	clear_3d_array(char ***alias, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free_2d_array((void ***)&alias[i]);
		++i;
	}
	ft_free((void *)alias);
}

char	***get_alias(char ***init_alias)
{
	static char	***alias = NULL;

	if (alias == NULL)
	{
		alias = init_alias;
		return (NULL);
	}
	else
		return (alias);
}

char	**add_alias(char **array, char *line, int start)
{
	char	**alias_val;
	int	i;

	i = 0;
	while (line[start + i] != '\n' && line[start + i] != '\0')
	{
		if (line[start + i] == '\n' || line[start + i] == '\0')
			return (NULL);
		if (line[start + i] == '"')
			break ;
		++i;
	}
	line[start + i] = '\0';
	alias_val = ft_split(line + start, ' ');
	if (alias_val == NULL)
		return (ft_free(alias_val),
			error_log("add_alias: ft_split failed:", true), NULL);
	i = 0;
	while (alias_val[i] != NULL)
	{
		array[1 + i] = alias_val[i];
		++i;
	}
	array[i + 1] = NULL;
	return (ft_free(alias_val), array);
}

char	
