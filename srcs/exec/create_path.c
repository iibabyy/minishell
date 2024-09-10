#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>


char *get_path(char *command, char **paths)
{
    int i;
    char *finalpath;

    i = 0;
    if (command == NULL || access(command, X_OK) == 0)
            return(command);
    while(paths[i])
    {
        paths[i] = ft_re_strjoin(paths[i], "/");
        if(!paths[i])
            print_err_and_exit(NULL, 1, false);
        i++;
    }
    i = 0;
    while(paths[i])
    {
        finalpath = ft_re_strjoin(paths[i], command);
        if(!finalpath)
            print_err_and_exit(NULL, 1, false);
        if (access(finalpath, X_OK) == 0)
            return(finalpath);
        i++;
    }
    return(command);
}

char *create_command_path(t_exec_data *data, t_command *command)
{
        data->path_to_join = ft_split(ft_getenv("PATH"), ':');
        if (data->path_to_join == NULL)
        {
           data->command_path = ft_strdup(command->command[0]);
           return (data->command_path);
        }
        if (command && command->command)
            data->command_path = get_path(command->command[0], data->path_to_join);
        return(data->command_path);
}
