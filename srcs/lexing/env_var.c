#include "lexing.h"

char	*replace_env_vars(char *input)
{
	int		i;
	int		y;
	char	**array;
	int		start;

	(i = 0, y = 0);
	if (input == NULL || count_char(input, '$') == 0)
		return (input);
	array = ft_malloc(sizeof(char *) * (count_char(input, '$') * 10));
	if (array == NULL)
		return (ft_free(input), NULL);
	while (input[i] != '\0')
	{
		start = i;
		while (input[i] != '$' && input[i] != '\0')
			++i;
		array[y] = ft_substr(input, start, i - start);
		if (array[y++] == NULL)
			return (ft_free(input), free_2d_array((void ***)&array), NULL);
		if (input[i] == '\0')
			break ;
		array[y] = env_to_string(input, &i);
		if (array[y++] == NULL)
			return (ft_free(input), free_2d_array((void ***)&array), NULL);
	}
	array[y] = NULL;
	return (ft_free(input), str_join_2d_and_free(array, ""));
}

char	*env_to_string(char	*str, int *dollar_index)
{
	char	*var;
	char	*env;
	int		start;

	start = ++*dollar_index;
	if (ft_isalpha(str[*dollar_index]) == false && str[*dollar_index] != '_')
	{
		++*dollar_index;
		var = ft_strdup("");
		return (var);
	}
	while (ft_isalnum(str[*dollar_index]) == true || str[*dollar_index] == '_')
		++*dollar_index;
	var = ft_substr(str, start, *dollar_index - start);
	if (var == NULL)
		return (NULL);
	env = getenv(var);
	ft_free(var);
	if (env == NULL)
		return (ft_strdup(""));
	env = ft_strdup(env);
	return (env);
}
