#include "parsing_utils.h"

/*
Fork() ? :
bash can see next syntaxes errors before executing pipe.
Is it because he just save all the here_docs, then check the errors,
and then executing here_doc ?
or because he just fork() the here_doc and continue the parsing ?
(and wait() for the process(es) to finish the here_docs)


*/

int	add_here_doc(t_command *command, t_token **token)
{
	int	fd;


}

void	add_pid
