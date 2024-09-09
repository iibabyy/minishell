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
int test_cd(char *str)
{
	if (chdir(str) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	str = replace_newline(str);
    if (strchr(str, '/'))
    {
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
    pid_t pid;
    int status = 0;
    t_exec_data *exec;

    if (should_fork(command))
    {
        pid = fork();
        if (pid == 0)
        {
            set_child_signals();
            exec = ft_malloc(sizeof(t_exec_data));
            init_data(exec, command);
            if (open_redirections(command) == EXIT_FAILURE)
                free_and_exit(EXIT_FAILURE);
            ((dup2(command->infile, STDIN_FILENO), dup2(command->outfile, STDOUT_FILENO)));
            if (command->command == NULL || command->command[0] == NULL)
                (ft_close(&command->outfile), ft_close(&command->infile), free_and_exit(EXIT_FAILURE));
            execve(exec->command_path, command->command, env_tab());
            if(access(command->command[0], X_OK) == 0 && 
                ft_strlen_2d(command->command) == 1 && command->previous == NULL )
            {
                if (test_cd(command->command[0]) == EXIT_SUCCESS)
                    free_and_exit(250);
            }
            execve_error(command->command[0]);
        }
        waitpid(pid, &status, 0);
		set_exit_code(status);
		if (get_code(0, false) == 128 + SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		if (get_code(0, false) == 128 + SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
    }
    return(set_exit_code(exec_builtin(command)), get_code(0, false));
}

int   exec_single_command(t_command *command)
{
    t_exec_data *exec;

	set_child_signals();
    exec = ft_malloc(sizeof(t_exec_data));
	init_data(exec, command);
	if (open_redirections(command) == EXIT_FAILURE)
        free_and_exit(EXIT_FAILURE);
	dup2(command->infile, STDIN_FILENO);
    dup2(command->outfile, STDOUT_FILENO);
    if (command->command == NULL || command->command[0] == NULL)
		(ft_close(&command->outfile), ft_close(&command->infile), free_and_exit(EXIT_FAILURE));
	execve(exec->command_path, command->command, env_tab());
    execve_error(command->command[0]);
    return(0);
}
