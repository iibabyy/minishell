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

void redirect_std(t_command *command)
{
        open_redirections(command); 
        dup2(command->infile, STDIN_FILENO);
        dup2(command->outfile, STDOUT_FILENO);
}

/*only one command*/
void    exec_single_command(t_command *command)
{
    pid_t pid;
    t_exec_data *exec;

    if (command == NULL)
        return;
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
        redirect_std(command);
        execve(exec->command_path, command->command, NULL);     
    }
    else
    {
       wait(NULL);
    }
}
/*function to dup fd to std*/


/*change infile and outfile when opeqrtor  is pipe FD[0] for left FD[0] for right */

void close_fds(int *fd, t_command *command)
{
    close(fd[0]);
    close(fd[1]);
    (void)fd;
    if (command->infile != 0)
        close(command->infile);
    if (command->outfile != 1)
        close(command->outfile);
}
void exec_command(t_command *command)
{
    int fd[2];
    pid_t pid;
    t_exec_data *exec;

    if (command == NULL)
        return;
    fprintf(stderr, "%d\n", command->infile);
    if(command->previous->type == PIPE)
    {
        if (pipe(fd) == - 1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        if (command->left)
            exec_command(command->previous->left);
        if(command->right)
            exec_command(command->previous->right);
        return;
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
        open_redirections(command);
        redirect_std(command);
        execve(exec->command_path, command->command, NULL);     
    }
    else
    {
    //  close_fds(fd, command);
       wait(NULL);
    }
}