#include "../../includes/libft.h"

char	*read_file(int fd)
{
	char	*temp;
	char	*str;

	temp = get_next_line(fd);
	if (temp == NULL)
		return (NULL);
	while (temp != NULL)
	{
		str = ft_re_strjoin(str, temp);
		ft_free(temp);
		if (str == NULL)
			return (NULL);
		temp = get_next_line(fd);
	}
	return (str);
}