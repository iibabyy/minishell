#ifndef EXEC_H
#define EXEC_H

typedef struct s_exec_data
{
    char *command_path;
    char **path_to_join;
    
}     t_exec_data;


void exec_command(t_command *command);

#endif