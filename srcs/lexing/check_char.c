#include "lexing.h"

bool	is_meta_char(char *input, int index)
{
	char	c;

	c = input[index];
	if (c == '\0')
		return (false);
	else if (ft_strchr("|<>$* ", c) != NULL)
		return (true);
	else if (c == '&' && input[index + 1] == '&')
		return (true);
	else if (c == '&' && input[index - 1] == '&')
		return (true);
	else
		return (false);
}

//	return true if input[index] is an operator
//	return false if input[index] is not operator
//	operators are |, &, (, )
//	note that '&' is not handle, unlike '&&'
bool	is_operator(char *input, int index)
{
	if (ft_strchr("|()", input[index]) != NULL)
		return (true);
	else if (input[index] == '&' && input[index + 1] == '&')
		return (true);
	else
		return (false);
}

//	return true if c is an redirection
//	return false if c is not redirection
bool	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	is_quotes(char c)
{
	if (c == '"' || c == 39)
		return (true);
	else
		return (false);
}

int	quotes_size(char **input, int start, char eof)
{
	char	*temp;
	int		i;
	
	i = 0;
	while (1)
	{
		if ((*input)[start + i] == '\0')
		{
			temp = get_input(&eof, QUOTES_PROMPT, true);
			*input = ft_re_strjoin(*input, temp);
			if (temp == NULL || *input == NULL)
				return (error_log("quotes_size: get_input() failed", false),
					ft_free(*input), ft_free(temp), -1);
		}
		if ((*input)[start + i] == eof)
			break ;
		++i;
	}
	return (i);
}