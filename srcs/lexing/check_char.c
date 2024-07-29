#include "lexing_utils.h"

bool	is_meta_char(char *input, int index)
{
	char	c;

	c = input[index];
	if (ft_strchr("'|<>()$* ", c) != NULL)
		return (true);
	else if (c == 34)
		return (true);
	else if (c == '&' && input[index + 1] == '&')
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
	char		*one_sized;
	int			i;
	char		c;

	(one_sized = "()$*", c = input[start], i = 1);
	if (c == '"' || c == 39)
	{
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
	if (ft_strchr(one_sized, c) != NULL)
		return (1);
	else if (input[start + 1] == c)
		return (2);
	else
		return (1);
}
