#include "lexing.h"

bool	is_meta_char(char *input, int index)
{
	char	c;

	c = input[index];
	if (c == '\0')
		return (false);
	else if (ft_strchr("'|<>()$* ", c) != NULL)
		return (true);
	else if (c == 34)
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

int	metachar_size(char *input, int start)
{
	static bool	err = false;
	int			i;
	char		c;

	(c = input[start], i = 0);
	if (c == '"' || c == 39)
	{
		++i;
		while (input[start + i] != c && input[start + i] != '\0')
			++i;
		if (input[start + i] == '\0')
		{
			if (err == false)
					(err = true, print_err("opened quotes detected", false));
			return (-1);
		}
		return (i + 1);
	}
	while (is_meta_char(input, start + i) == true && input[start + i] != ' ')
		++i;
	return (i);
}
