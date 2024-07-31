#include "parsing.h"

int	token_to_operator_type(t_token *token)
{
	if (token == NULL)
		return (-1);
	else if (ft_strcmp(token->content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token->content, "||") == 0)
		return (OR);
	else if (ft_strcmp(token->content, "&&") == 0)
		return (AND);
	else
		return (-1);
}
