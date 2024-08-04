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

int	char_type(char *str, int index)
{
	char	c;

	c = str[index];
	if (is_quotes(c) == true)
		return (WORD);
	if (is_redirection(c) == true)
		return (REDIRECTION);
	if (ft_strchr("|()", c) != NULL)
		return (OPERATOR);
	if (c == '&' && str[index + 1] == '&')
		return (OPERATOR);
	error_log("unknow token\n", false);
	return (-1);
}
