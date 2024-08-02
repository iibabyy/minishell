#include "features.h"

int	init_aliases()
{
	char	**aliases;
	int	mshrc_fd;

	mshrc_fd = open(MSHRC, O_RDONLY);
	if (mshrc_fd == -1)
		return (get_aliases(NULL), EXIT_FAILURE);
	aliases = search_aliases(mshrc_fd);
}

char **search_aliases(int fd)
{
	char	**aliases;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	while ()
	{
		/* code */
	}
	
}
