#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <limits.h>

# include "structs.h"
# include "libft.h"
# include "garbage_collector.h"
# include "error.h"

extern volatile sig_atomic_t g_signal;

#endif