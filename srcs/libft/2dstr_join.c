#include "../../includes/libft.h"

static void	free_arrays(char **join, char **str1, char **str2);
static void	free_strs(char **str1, char **str2);
static int	arrays_size(char **str1, char **str2);

char	**str2d_join(char **str1, char **str2)
{
	char	**join;
	int		i;
	int		j;

	join = ft_malloc(sizeof(char *) 
			* (ft_strlen_2d(str1) + ft_strlen_2d(str2) + 1));
	if (join == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i] != NULL)
	{
		join[++j] = ft_strdup(str1[i]);
		if (join[j] == NULL)
			return (free_2d_array((void ***)&join), NULL);
	}
	i = -1;
	while (str2[++i] != NULL)
	{
		join[++j] = ft_strdup(str2[i]);
		if (join[j] == NULL)
			return (free_2d_array((void ***)&join), NULL);
	}
	join[j] = NULL;
	return (join);
}

char	**str2djoin_and_free(char **str1, char **str2)
{
	char	**join;
	int		i;
	int		j;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	join = ft_malloc(sizeof(char *) * (arrays_size(str1, str2) + 1));
	if (join == NULL)
		return (free_arrays(join, str1, str2), NULL);
	i = -1;
	j = -1;
	while (str1[++i] != NULL)
	{
		join[++j] = ft_strdup(str1[i]);
		if (join[j] == NULL)
			return (free_arrays(join, str1, str2), NULL);
	}
	i = -1;
	while (str2[++i] != NULL)
	{
		join[++j] = ft_strdup(str2[i]);
		if (join[j] == NULL)
			return (free_arrays(join, str1, str2), NULL);
	}
	return (free_strs(str1, str2), join[j] = NULL, join);
}

static int	arrays_size(char **str1, char **str2)
{
	return (ft_strlen_2d(str1) + ft_strlen_2d(str2));
}

static void	free_strs(char **str1, char **str2)
{
	free_2d_array((void ***)&str1);
	free_2d_array((void ***)&str2);
}

static void	free_arrays(char **join, char **str1, char **str2)
{
	free_2d_array((void ***)&join);
	free_2d_array((void ***)&str1);
	free_2d_array((void ***)&str2);
}
