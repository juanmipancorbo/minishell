#include "../include/minishell.h"

pid_t ft_exec_1(char **args, int (*pipe_fd)[2])
{
	pid_t pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0][READ_END]);
		dup2(pipe_fd[0][WRITE_END], STDOUT_FILENO);
		close(pipe_fd[0][WRITE_END]);
		execv(args[0],args);
	}
	else
	{
		// cerar files descriptor
		close(pipe_fd[0][WRITE_END]);
	}
	return pid;
}

pid_t ft_exec_2(char **args, int (*pipe_fd)[2])
{
	pid_t pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[1][READ_END]);
		
		dup2(pipe_fd[0][READ_END], STDIN_FILENO);
		close(pipe_fd[0][READ_END]);

		dup2(pipe_fd[1][WRITE_END], STDOUT_FILENO);
		close(pipe_fd[1][WRITE_END]);
		execv(args[0],args);
	}
	else
	{
		// cerar files descriptor
		close(pipe_fd[0][READ_END]);
		close(pipe_fd[1][WRITE_END]);
	}
	return pid;
}

pid_t ft_exec_3(char **args, int (*pipe_fd)[2])
{
	pid_t pid = fork();
		if (pid == 0)
	{
		dup2(pipe_fd[1][READ_END], STDIN_FILENO);
		close(pipe_fd[1][READ_END]);
		
		execv(args[0],args);
	}
	else
	{
		close(pipe_fd[1][READ_END]);

	}
	return pid;
}
int main(void)
{
	char *arg1[3]={"/bin/ls", "-l", NULL};
	char *arg2[3]={"/bin/grep", "pipe", NULL};
	char *arg3[3]={"/bin/wc", "-l", NULL};
	int pipe_fd[2][2];
	pid_t pid[3];

	pipe(pipe_fd[0]);
	pipe(pipe_fd[1]);
	pid[0] = ft_exec_1(arg1,pipe_fd);
	pid[1] = ft_exec_2(arg2,pipe_fd);
	pid[2] = ft_exec_3(arg3,pipe_fd);

	waitpid(pid[0],NULL,0);
	waitpid(pid[1],NULL,0);
	waitpid(pid[2],NULL,0);

	return 0;

}