#include "minishell.h"

int checking_line(char  *line)
{
	int	i;

	i = 0;
	line = ft_strtrim(line , " \n");
	if(line[i] == '|' || line[i] == '&' || line[i] == ')')
		return(-1);
	while(line[i])
		++i;
	if(i > 0)
	{
		if(line[i - 1] == '|' || line[i - 1] == '&' || line[i - 1] == ')')
			return(-1);
	}
	return(0);
}

int checking_cote(char *line)
{
	int i;
	char double_cote;
	char single_cote;

	int number_single = 0;
	int number_double ;
	double_cote = 34;
	single_cote = 39;


	i = 0;
}