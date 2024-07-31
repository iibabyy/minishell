#include "parsing.h"

/*
Fork() ? :	(No)
bash can see next syntaxes errors before executing pipe.
Is it because he just save all the here_docs, then check the errors,
and then executing here_doc ?
or because he just fork() the here_doc and continue the parsing ?
(and wait() for the process(es) to finish the here_docs)

Instead :

Save and open ? :

Saving all the base redirections '<', '>' and '>>' in a chained list,
and all the Here_docs in an other chained list.
Add the corresponding command, files,
and token ('<', '<<', '>', '>>') into the struct.
Don't do the redirections parsing now (for example '<<<<<' must not arrest us !)
Then, when we finish to parse the input,
start parsing and opening all the redirections:
starting with all the here_doc,
then all the base redirections.
Like that, we can reproduce the way bash handle redirections errors,
mainly the here_docs errors.

