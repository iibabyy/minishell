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

int	args_number(t_token *token)
{
	int	i;

	token = token->next;
	while (token != NULL && token->type != OPERATOR)
	{
		if (token->type == REDIRECTION)
		{
			if (token->next == NULL || token->next->next == NULL)
				return (i);
			token = token->next->next;
		}
		++i;
		token = token->next;
	}
	return (i);
}

int	redirections_number(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		if (token->type == REDIRECTION)
			++i;
		token = token->next;
	}
	return (i);
}
