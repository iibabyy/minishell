#include "wildcard.h"

char	*expand_wildcard(char *input)
{
	char 	**temp;
	int		i;

	if (count_char(input, '*') == 0)
		return (input);
	temp = ft_split(input, ' ');
	if (temp == NULL)
		return (NULL);
	i = -1;
	while (temp[++i] != NULL)
	{
		if (count_char(temp[i], '*') == 0)
			continue ;
		temp[i] = list_files(temp[i], temp);
		if (temp[i] == NULL)
			return (free_2d_array((void ***)&temp), NULL);
	}
	return (str_join_2d_and_free(temp, " "));
}

char	*list_files(char *str, char **input)
{
	DIR				*dir;
	struct dirent	*file;
	char			*list;

	if (str == NULL || (dir = opendir("./")) == NULL)
		return (NULL);
	list = NULL;
	while ((file = readdir(dir)) != NULL)
	{
		if (is_valid_name(file->d_name, str, input) == false)
			continue ;
		if (list != NULL)
		{
			list = ft_re_strjoin(list, " ");
			if (list == NULL)
				return (closedir(dir), NULL);
		}
		list = ft_re_strjoin(list, file->d_name);
		if (list == NULL)
			return (closedir(dir), NULL);
	}
	if (list == NULL)
		return (closedir(dir), str);
	return (closedir(dir), list);
}

bool	is_valid_name(char *name, char *original, char **input)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (name == NULL || (ft_strncmp(name, ".", 1) == 0 && original[0] != '.'))
		return (false);
	while (original[i] != '\0')
	{
		if (original[i] == '*' && quotes_or_parenthesis_2d(input, original, i) == 0)
		{
			if (original[++i] == '\0')
				return (true);
			while (original[i] == '*')
				++i;
			while (name[j] != original[i] && name[j] != '\0')
				++j;
		}
		else
		{
			if (name[j++] != original[i++])
				return (false);
		}
	}
	return (true);
}
