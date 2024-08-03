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
