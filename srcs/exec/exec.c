#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>
/*int execve(const char *fichier, char *const argv[], char *const envp[]);  
*/

/*char * getenv( const char * varName );*/

/* int access(const char *pathname, int mode); */


/*functions to check if the avsolute path of the command exit and return it*/
char *get_path(char *command, char **paths)
{
    int i;
    char *finalpath;

    i = 0;
    if (access(command, X_OK) == 0)
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
    return(NULL);
}

void redirect_std(t_command *command, int *fd, bool is_pipe)
{
        if (command->infile == STDIN_FILENO)
        {
            if (is_pipe)
            {
                dup2(fd[0], STDIN_FILENO);
            }
            close(fd[0]);
        }
        else
        {
            if (dup2(command->infile, STDIN_FILENO) == -1)
                    print_err_and_exit("dup", 1, false);
            close(command->infile);
            if (is_pipe)
                close(fd[0]);
        }
        if (command->outfile == STDOUT_FILENO)
        {
            if (is_pipe)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        else
        {
            if (dup2(command->outfile, STDOUT_FILENO) == -1)
                    print_err_and_exit("dup", 1, false);
            close(command->outfile);
            if (is_pipe)
                close(fd[1]);
        }
}
    
void exec_command(t_command *command)
{
    t_exec_data *exec;
    int fd[2];
    pid_t pid;
    bool is_pipe;
    
    if (command == NULL)
        return;
    if(command->type == PIPE)
    {
        exec_command(command->right);
        return;
    }
    if (command->previous && command->previous->type == PIPE)
    {
        if (pipe(fd) == - 1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        is_pipe = true;
    }
    else
    {
        is_pipe = false;
    }

    pid = fork();
    if (pid == 0)
    {
        exec = ft_calloc(1, sizeof(t_exec_data));
        if (exec == NULL)
            print_err_and_exit(NULL, 1, false);
        exec->path_to_join = ft_split(getenv("PATH"), ':');
        if(exec->path_to_join)
        {
            exec->command_path =  get_path(command->command[0], exec->path_to_join);
            if(exec->command_path == NULL)
            {
                ft_putstr_fd("bash : Command not found", 2);
                print_err_and_exit(command->command[0] , 1, false);
            }
        }

        redirect_std(command, fd, is_pipe);
        execve(exec->command_path, command->command, NULL);     
    }
    else
    {
       wait(NULL);
       if(command->previous)
       {
            exec_command(command->previous);
            return;
       }
    }
}