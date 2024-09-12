#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

int	update_pwd(char *old_pwd);

bool is_built_in(t_command *node)
{
    if (node->command == NULL || node->command[0] == NULL)
		return (false);
	if(ft_strcmp("echo", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("cd", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("pwd", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("unset", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("export", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("exit", node->command[0]) == 0)
        return (true);
    if(ft_strcmp("env", node->command[0]) == 0)
        return (true);
    return(false);
}
bool test_cd(t_command *command)
{
	struct stat	buf;
	if (command->previous != NULL || command->type != COMMAND)
		return (false);
	if (command->redirections != NULL)
		return (false);
	if (command->command == NULL || command->command[0] == NULL
		|| command->command[1] != NULL)
		return (false);
	if(access(command->command[0], X_OK) != 0)
		return (false);
	if (stat(command->command[0], &buf) == -1)
		return(false);
	if (S_ISDIR(buf.st_mode))
        return (true);
	return (false);
}
int exec_cd(char *str)
{
    char **cd_args;

	cd_args = ft_malloc(sizeof(char *) * 3);
    cd_args[0] = ft_strdup("cd");
    cd_args[1] = ft_strdup(str);
    cd_args[2] = NULL;
    return(cd(cd_args));
}

void execve_error(char *str)
{
    struct stat	buf;
    
	str = replace_newline(str);
    if (strchr(str, '/'))
    {
        if (stat(str, &buf) == -1)
        {
            if(errno == EACCES)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(str, 2);
                ft_putendl_fd(": Permission denied ", 2);
                free_and_exit(126);
            }
        }
        else
        {
            if (S_ISREG(buf.st_mode))
                free_and_exit(0);
        }
        ft_putstr_fd("minishell: No such file or directory: ", 2);
        ft_putendl_fd(str, 2);
        free_and_exit(127);
    }
    else
    {
        ft_putstr_fd("minishell : Command not found : ", 2);
        ft_putendl_fd(str, 2);
        free_and_exit(127);
    }
}
int   exec_single(t_command *command)
{
    pid_t	pid;

    command->single = true;
    if (should_fork(command))
    {
        pid = ft_fork(command);
        if (pid == 0)
			exec_command(command);
		if (ft_waitpid(pid, command) == 250)
			last_status_code(exec_cd(command->command[0]), SET);
		return (get_status());
    }
    return(last_status_code(exec_command(command), SET), get_status());
}
void check_directory(t_command *command)
{
    if(ft_strchr(command->command[0] , '/'))
    {
        if (access(command->command[0], F_OK) == 0 && (chdir(command->command[0]) == 0 || errno == EACCES))
        {
            ft_putstr_fd("minishell : ", 2);
            ft_putstr_fd(command->command[0], 2);
            ft_putendl_fd(": Is a directory", 2);
            free_and_exit(126);
        }
    }
}

int   exec_single_command(t_command *command)
{
    t_exec_data *exec;

	set_child_signals();
	exec = ft_malloc(sizeof(t_exec_data));
	if (open_redirections(command) == EXIT_FAILURE)
		free_and_exit(EXIT_FAILURE);
    if (command->single == true && test_cd(command))
    {
        free_and_exit(250);
    }
	init_data(exec, command);
	if (command->command == NULL || command->command[0] == NULL)
		(ft_close(&command->outfile), ft_close(&command->infile), free_and_exit(EXIT_FAILURE));
	execve(exec->command_path, command->command, env_tab());
	if (test_cd(command) == true)
		free_and_exit(250);
	(ft_close(&command->outfile), ft_close(&command->infile));
	execve_error(command->command[0]);
	return(get_status());
}
