#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "exec/my_srcs/pipex.h"
#include "minishell.h"

void	ft_comand_back(t_comand **lst, t_comand *new)
{
	t_comand	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->previous = temp;
}

t_comand	*create_node(char *data)
{
	t_comand	*new_node;

	new_node = malloc(sizeof(t_comand));
	new_node->data = data;
	if(*data != '|')
		new_node->type = 0;
	else
		new_node->type = 1;
	new_node->next = NULL;
	return (new_node);
}
void define_comand(char **comand, t_comand **x)
{
	int i;
	t_comand *temp;

	i = 0;
	while(comand[i])
	{
		temp = create_node(comand[i]);
		ft_comand_back(x, temp);
		i++;
	}
}
int main (int ac, char **av)
{
	(void)av;
	(void)ac;
	char *data;
	int i = 0;
	char **comand;
	t_comand *x;

	x = malloc(sizeof(t_comand));
	comand =  malloc(sizeof(char*) * 2);
	while (1)
	{
		ft_putstr_fd("\033[0;36m", 2);
		ft_putstr_fd("🇲🇱inishell⥇ ", 2);
		ft_putstr_fd("\033[0m", 2);
		data = get_next_line(0);
		while(data[i])
		{
			if (data[i] == '\n')
				data[i] = '\0';
			i++;
		}
		if( parsing_cote(data) == -1)
			printf("Error Bad inputs\n");
		else
			printf("good inputs\n");

		// comand = ft_split(data, 32);
		// define_comand(comand, &x);
		// x = x->next;
	}
}