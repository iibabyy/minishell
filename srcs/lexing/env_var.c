#include "lexing.h"

char	*replace_env_vars(char *input)
{
	int		i;
	int		y;
	char	**arrays;
	int		start;

	i = 0;
	arrays = ft_malloc(sizeof(char *) * (count_char(input, '$') + 1));
	if (arrays == NULL)
		return (ft_free(input), NULL);
	while (input[i] != '\0')
	{
		start = i;
		while (input[i] != '$' && input[i] != '\0')
			++i;
		arrays[y] = ft_substr(input, start, i - start);
		if (arrays[y++] == NULL)
			return (free_2d_array((void ***)&arrays), ft_free(input), NULL);
		if (input[i] == '\0')
			break ;
		arrays[y] = env_to_string(input, &i);
		if (arrays[y++] == NULL)
			return (free_2d_array((void ***)&arrays), ft_free(input), NULL)
	}
	arrays[y] = NULL;
	return (join_2d_array(arrays));
}

char	*env_to_string(char	*str, int *i)
{
	char	*var;
	char	*env;
	int		start;

	start = ++*i;
	if (ft_isalpha(str[*i]) == false && str[*i] != '_')
	{
		++*i;
		var = ft_strdup("");
		return (var);
	}
	while (ft_isalnum(str[*i]) == true || str[*i] == '_')
		++*i;
	var = ft_substr(str, start, i);
	if (var == NULL)
		return (NULL);
	env = getenv(var);
	ft_free(var);
	if (env == NULL)
	{
		env = ft_strdup("");
	}
	return (env);
}

