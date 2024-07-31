#include "lexing.h"

t_token	*init_token(char **input, int start)
{
	t_token	*new_token;
	char	*content;
	int		len;

	new_token = ft_calloc(1, sizeof(t_token) * 1);
	if (new_token == NULL)
		return (print_err("init_token: ft_malloc() failed:", true), NULL);
	new_token->next = NULL;
	new_token->type = char_type(*input, start);
	len = metachar_size(input, start);
	if (len == -1 || new_token->type == -1)
		return (ft_free(new_token), NULL);
	if (new_token->type == STRING)
	{
		len -= 2;
		start += 1;
	}
	content = ft_substr(*input, start, len);
	if (content == NULL)
		return (print_err("init_token: ft_substr() function failed:", true),
			ft_free(new_token), NULL);
	new_token->content = content;
	return (new_token);
}

int	char_type(char *str, int index)
{
	char	c;

	c = str[index];
	if (is_quotes(c) == true)
		return (STRING);
	if (is_redirection(c) == true)
		return (REDIRECTION);
	if (ft_strchr("|()", c) != NULL)
		return (OPERATOR);
	if (c == '&' && str[index + 1] == '&')
		return (OPERATOR);
	fprintf(stderr, "unknow token '%c'\n", c);
	return (-1);
}
