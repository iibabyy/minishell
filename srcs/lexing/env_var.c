/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:33:50 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/08 00:37:33 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*replace_env_vars(char *input)
{
	char	**array;
	char	*new_input;
	if(input == NULL)
		return(NULL);
	if (input && count_char(input, '$') == 0)
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
	array = ft_malloc(sizeof(char *) * (count_char(input, '$') * 2 + 2));
	if (array == NULL)
		return (malloc_failed("replace_dollars"), NULL);
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
	if (str[*dollar_index] == '?')
		return (++*dollar_index, ft_itoa(get_code(0, false)));
	if (ft_isalpha(str[*dollar_index]) == false && str[*dollar_index] != '_')
		return (NULL);
	while (ft_isalnum(str[*dollar_index]) == true || str[*dollar_index] == '_')
		++*dollar_index;
	var = ft_substr(str, start, *dollar_index - start);
	if (var == NULL)
		return (NULL);
	env = ft_getenv(var);
	ft_free(var);
	if (env == NULL)
		return (NULL);
	env = ft_strdup(env);
	if (env == NULL)
		return (error_log("env_to_string: ft_strdup failed", false), NULL);
	return (env);
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

int	replace_tokens_env_vars(t_token *token)
{
	t_token	*temp_token;
	t_token	*temp;

	if (token == NULL)
		return (EXIT_SUCCESS);
	while (token != NULL)
	{
		if (token->content != NULL && ft_strchr(token->content, '$') != NULL)
		{
			token->content = replace_env_vars(token->content);
			if (token->content == NULL)
				return (EXIT_FAILURE);
			temp_token = input_to_tokens(token->content);
			if (temp_token == NULL)
				return (EXIT_FAILURE);
			temp = token->next;
			last_token(temp_token)->next = token->next;
			token->next = temp_token;
			token = temp;
		}
		else
			token = token->next;
	}
	return (EXIT_SUCCESS);
}
