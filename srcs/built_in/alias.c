#include "built_in.h"
#include "../features/features.h"

int	alias(char **arg)
{
	static char	***aliases = NULL;
	char		**alias;
	int			i;
	int			status;

	if (aliases == NULL)
		aliases = init_new_aliases();
	if (aliases == NULL)
		return (EXIT_FAILURE);
	i = 0;
	status = EXIT_SUCCESS;
	while (arg[++i] != NULL)
	{
		if (parse_alias_arg(arg[i]) == EXIT_FAILURE)
		{
			status = EXIT_FAILURE;
			continue ;
		}
		alias = create_alias(arg[i]);
		if (alias == NULL)
			continue ;
		add_back_aliases(aliases, alias);
	}
	return (status);
}

char **create_alias(char *arg)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	while (arg[i] != '=')
		++i;
	if (arg[++i] == '"')
		return (line_to_alias(arg));
	str = insert_str(arg, "\"", i);
	if (str == NULL)
		return (NULL);
	while (arg[i] != ' ' && arg[i] != '\0')
		++i;
	temp = str;
	str = insert_str(str, "\"", i + 1);
	ft_free(temp);
	if (str == NULL)
		return (NULL);
	str = ft_strjoin("alias ", str);
	return (line_to_alias(str));
}

int	parse_alias_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == ' ' || arg[i] == '\0')
		return (print_err("export: wrong argument format", false),
				EXIT_FAILURE);
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (print_err("alias: wrong argument format", false),
				EXIT_FAILURE);
	while (arg[i] != '=' && arg[i] != '\0' && arg[i] != ' ')
		++i;
	if (arg[i] == ' ' || arg[i] == '\0')
		return (print_err("alias: wrong argument format", false),
				EXIT_FAILURE);
	if (arg[++i] == ' ' || arg[i] == '\0')
		return (print_err("alias: wrong argument format", false),
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	add_back_aliases(char ***aliases, char **alias)
{
	int	i;

	i = 0;
	while (aliases[i] != NULL && i < MAX_ALIAS)
		++i;
	if (i >= MAX_ALIAS)
		return (error_log("alias: max aliases reached. Cannot add one", false));
	aliases[i] = alias;
	aliases[i + 1] = NULL;
}

char	***init_new_aliases(void)
{
	char	***aliases;

	aliases = get_alias(NULL);
	if (aliases != NULL)
		return (aliases);
	aliases = ft_calloc(MAX_ALIAS, sizeof(char **));
	if (aliases == NULL)
		return (NULL);
	aliases[0] = NULL;
	(void)get_alias(aliases);
	return (aliases);
}
