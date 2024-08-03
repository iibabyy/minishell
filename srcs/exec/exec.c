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
        open(command->outfile->file->content, command->outfile->o_flags);
        printf("Nom de l'outfile: %s\n", command->outfile->file->content);
        if (dup2(command->infile_fd, STDIN_FILENO) == -1)
                print_err_and_exit("dup", 1, false);
        close (command->infile_fd);
        printf("Num de l' infile: %d\n", command->infile_fd);
        if (dup2(command->outfile_fd, STDOUT_FILENO) == -1)
                print_err_and_exit("dup", 1, false);
         close (command->outfile_fd);
        printf("Num de l'outfile %d\n", command->outfile_fd);
}
void exec_command(t_command *command)
{
    t_exec_data *exec;
    //int fd[2];
    pid_t pid;

    /*if (pipe(fd) == - 1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }*/

   if (command->type == PIPE)
   {
         exec_command(command->left);
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
        /*printf("herrrre\n");
        redirect_std(command);*/
        execve(exec->command_path, command->command, NULL);     
    }
    else
       wait(NULL);
       pipe(fd);
       exec(command->previous);
}