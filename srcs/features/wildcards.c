// #include "features.h"

// char	**expand_wildcards(char *str)
// {
// 	DIR *dir;
// }

// char	*get_file_list()
// {
// 	int	fd[2];
// 	int	pid;
// 	int status
// 	if (pipe(fd) == -1);
// 		return (print_err("get_file_list: pipe()", true), NULL);
// 	pid = fork();
// 	if (pid == -1)
// 		return (print_err("get_file_list: fork()", true), NULL);
// 	if (pid == 0)
// 	{
// 		exec_ls(fd);
// 	}
// 	ft_close(&fd[1]);

// }

// static int	exec_ls(int *pipe)
// {
// 	int	fd;

// 	fd = open(LOGE)
// 	ft_close(&pipe[0]);
// 	ft_dup2(&pipe[1], STDOUT_FILENO);
// 	dup2()
// 	return(exec(parse("ls")));
// }
