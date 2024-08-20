/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:33:50 by ibaby             #+#    #+#             */
/*   Updated: 2024/08/20 22:18:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*replace_env_vars(char *input)
{
	char	**array;
	char	*new_input;

	if (count_char(input, '$') == 0)
		return (input);
	array = replace_dollars(input);
	if (array == NULL)
		return (NULL);
	new_input = str_join_2d_and_free(array, "");
	return (new_input);
}

char	**replace_dollars(char *input)
{
	char	**array;
	int		start;
	int		i;
	int		y;

	i = 0;
	y = 0;
	array = ft_malloc(sizeof(char *) * (count_char(input, '$') * 10));
	if (array == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		start = i;
		while (input[i] != '$' && input[i] != '\0')
			++i;
		array[y] = ft_substr(input, start, i - start);
		if (array[y++] == NULL)
			return (free_2d_array((void ***)&array), NULL);
		if (input[i] == '\0')
			break ;
		array[y] = env_to_string(input, &i);
		if (array[y++] == NULL)
			return (free_2d_array((void ***)&array), NULL);
	}
	return (array[y] = NULL, array);
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
	if (env == NULL)
		return (error_log("env_to_string: ft_strdup failed", false), NULL);
	return (split_env_var(env));
}

char    *split_env_var(char *env)
{
    char    **splited_env;
    char    *temp;
    int        i;

    splited_env = ft_split(env, '=');
    if (splited_env == NULL)
        return (NULL);
    i = -1;
    while (splited_env[++i] != NULL)
    {
        temp = splited_env[i];
        splited_env[i] = multi_strjoin(3, "\"", splited_env[i], "\"");
        ft_free(temp);
        if (splited_env[i] == NULL)
            return (error_log("split_env_var: multi_strjoin failed", false), NULL);
    }
    return (str_join_2d_and_free(splited_env, " "));
}
