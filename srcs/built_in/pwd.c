#include "built_in.h"

int	pwd(char **arg)
{
	char	*pwd;

	(void)arg;
	pwd = ft_getcwd();
	if (pwd == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	ft_free(pwd);
	return (EXIT_SUCCESS);
}

char	*ft_getcwd(void)
{
	char	*pwd;
	int		size;

	size = 128;
	pwd = ft_malloc(sizeof(char) * size);
	if (pwd == NULL)
		return (malloc_failed("ft_getcwd"), NULL);
	if (getcwd(pwd, size) != NULL)
		return (pwd);
	while (errno == ERANGE)
	{
		ft_free(pwd);
		size = size * 2;
		pwd = ft_malloc(sizeof(char) * size);
		if (pwd == NULL)
			return (malloc_failed("ft_getcwd"), NULL);
		if (getcwd(pwd, size) != NULL)
			return (pwd);
	}
	ft_free(pwd);
	return (NULL);
}
