#include "builtins.h"
#include "../exec/exec.h"

#define MAX_PATH_SIZE 1024

t_env_var	*new_env_var(char *variable, char *value);
void error_cd(t_command *cd)
{
    (void)cd;
    ft_putendl_fd("error", 2);
}
char *find_home_path(void)
{
    return (getenv("HOME"));
}
int change_directory(t_command *cd)
{
    char actual_path [MAX_PATH_SIZE];

    if (cd->command[1] == NULL)
    {
        cd->command[1] = find_home_path();
        if(cd->command[1] == NULL)
        {
            error_cd(cd);
            return (1);
        }
        new_env_var("PWD", getcwd(actual_path, MAX_PATH_SIZE));
    }
    if (getcwd(actual_path, MAX_PATH_SIZE) != NULL)
    {
        new_env_var("OLDPWD", actual_path);
        if(chdir(cd->command[1]) == -1)
        {
            ft_putstr_fd("cd : no such file or directory :", 2);
            ft_putendl_fd(cd->command[1], 2);
            return(1);
        }
        new_env_var("PWD", getcwd(actual_path, MAX_PATH_SIZE));
    }
    else
        fprintf(stderr, "fail\n");
    return(0);
}