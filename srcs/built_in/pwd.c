#include "built_in.h"

int	pwd(char **arg)
{
	char	*pwd;
	int		size;

	(void)arg;
	size = 128;
	pwd = ft_malloc(sizeof(char) * size);
	if (pwd == NULL)
		return (malloc_failed("pwd"), EXIT_FAILURE);
	if (getcwd(pwd, size) != NULL)
		return (printf("%s\n", pwd), EXIT_SUCCESS);
	while (errno == ERANGE)
	{
		ft_free(pwd);
		size = size * 2;
		pwd = ft_malloc(sizeof(char) * size);
		if (pwd == NULL)
			return (malloc_failed("pwd"), EXIT_FAILURE);
		if (getcwd(pwd, size) != NULL)
			return (printf("%s\n", pwd), EXIT_SUCCESS);
	}
	ft_free(pwd);
	return (EXIT_FAILURE);
}
