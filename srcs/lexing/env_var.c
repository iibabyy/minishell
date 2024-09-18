/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:33:50 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/18 16:53:07 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*replace_env_vars(char *input)
{
	char	**array;
	char	*new_input;

	if (input == NULL)
		return (input);
	if (count_char(input, '$') == 0)
		return (input);
	array = replace_dollars(input);
	if (array == NULL)
		return (input);
	new_input = str_join_2d_and_free(array, "");
	if (new_input == NULL)
		return (NULL);
	return (new_input);
}

char	**replace_dollars(char *input)
{
	char	**array;
	int		start;
	int		i;
	int		y;

	i = 0;
	y = -1;
	array = ft_calloc(count_char(input, '$') * 2 + 2, sizeof(char *));
	if (array == NULL)
		return (malloc_failed("replace_dollars"), NULL);
	while (input[i] != '\0')
	{
		start = i;
		if (next_valid_dollar(input, &i) == -1)
			return (free_2d_array((void ***)&array), NULL);
		array[++y] = ft_substr(input, start, i - start);
		if (array[y] == NULL)
			return (free_2d_array((void ***)&array), NULL);
		if (input[i] == '\0')
			break ;
		array[++y] = env_to_string(input, &i);
		if (array[y] == NULL)
			return (free_2d_array((void ***)&array), NULL);
	}
	return (array[++y] = NULL, array);
}

char	*transform_env_value(char *value)
{
	char	**temp;
	char	*str;

	temp = ft_split(value, ' ');
	if (temp == NULL)
		return (NULL);
	str = str_join_2d_and_free(temp, "' '");
	if (str == NULL)
		return (NULL);
	str = multi_strjoin(3, "'", str, "'");
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*env_to_string(char *str, int *dollar_index)
{
	char	*var;
	char	*env;
	int		start;

	start = ++*dollar_index;
	if (str[*dollar_index] == '?')
		return (++*dollar_index, ft_itoa(get_status()));
	if (ft_isalpha(str[*dollar_index]) == false && str[*dollar_index] != '_')
		return (NULL);
	while (ft_isalnum(str[*dollar_index]) == true || str[*dollar_index] == '_')
		++*dollar_index;
	var = ft_substr(str, start, *dollar_index - start);
	if (var == NULL)
		return (NULL);
	env = ft_strdup(ft_getenv(var));
	if (env == NULL)
		return (ft_strdup(""));
	if (is_in_quotes(str, start - 1) == 0
		&& is_in_parenthesis(str, start - 1) == 0)
	{
		env = transform_env_value(env);
		if (env == NULL)
			return (error_log("env_to_string: transform_env", false), NULL);
	}
	return (env);
}

char	*split_env_var(char *env)
{
	char	**splited_env;
	char	*temp;
	int		i;

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
			return (error_log("split_env_var: multi_strjoin failed", false),
				NULL);
	}
	return (str_join_2d_and_free(splited_env, " "));
}
