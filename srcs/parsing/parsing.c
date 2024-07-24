#include "minishell.h"
#include "parsing.h"

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
void set_quotes_status(t_quotes *data, char *line, int i)
{
		if (data->open_s == false && line [i] == (char)DOUBLE && data->open_d == false)
		{
			data->open_d = true;
			data->close_d = false;
		}
		else if (data->open_d == true && line [i] == DOUBLE)
		{
			data->open_d = false;
			data->close_d = true;
		}
		else if (data->open_d == false && line [i] == (char)SINGLE && data->open_s == false)
		{
			data->open_s = true;
			data->close_s = false;
		}
		else if (data->open_s == true && line [i] == SINGLE)
		{
			data->open_s = false;
			data->close_s = true;
		}
}
int checking_cote(t_quotes *data, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		set_quotes_status(data, line, i);
		++i;
	}
	if (data->close_d == true && data->close_s == true)
		return(0);
	else
		return(-1);
}

int parsing_cote(char *line)
{
	t_quotes *data;

	data = malloc(sizeof(t_quotes));
	if (!data)
		return(-1);
	ft_memset(data, 0, sizeof(data));
	data->close_s = true;
	data->close_d = true;
	data->open_d = false;
	data->open_s = false;
	return (checking_cote(data, line));
}
