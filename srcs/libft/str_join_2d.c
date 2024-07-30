#include "../../includes/libft.h"

char	*str_join_2d(char **str_2d)
{
	char	*str;
	int		i;

	if (str_2d == NULL)
		return (NULL);
	str = NULL;
	i = -1;
	while (str_2d[++i] != NULL)
	{
		str = ft_re_strjoin(str, str_2d[i]);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}
