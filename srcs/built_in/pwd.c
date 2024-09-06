# include "built_in.h"

int	pwd(char **arg)
{
	char	*pwd;
	int		size;

	size = 128;
	pwd = ft_malloc(sizeof(char) * size);
	if (getcwd(pwd, size) != NULL)
		return (pwd);
	if (errno != ERANGE)
		return (pwd_err(), err);
	while ()
}
