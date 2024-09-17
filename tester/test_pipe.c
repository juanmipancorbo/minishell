# include "../include/minishell.h"



pid_t exec_commnad(char **arg, int *pipe_fd, int i) {
	pid_t child;

	child = fork();
	if (child == 0)
	{
		if (i == 0)
		{
			close(pipe_fd[READ_END]);
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
			close(pipe_fd[WRITE_END]);
			execv(arg[0],arg);
		}
		else
		{
			close(pipe_fd[WRITE_END]);
			dup2(pipe_fd[READ_END], STDIN_FILENO);
			close(pipe_fd[READ_END]);
			execv(arg[0],arg);
		}
	}
	else
	{
		if (i == 0)
			close(pipe_fd[WRITE_END]);
		else
			close(pipe_fd[READ_END]);
		//wait(NULL);
	}
	return child;
}

int main(void)
{

	char *arg[3]={"/bin/ls", "-l", NULL};
	char *arg2[3]={"/bin/wc", "-l", NULL};
	int pipe_fd[2];
	pid_t child[2];

	pipe(pipe_fd);
	child[0] = exec_commnad(arg,pipe_fd,0);
	child[1] = exec_commnad(arg2,pipe_fd,1);
	waitpid(child[0],NULL,0);
	waitpid(child[1],NULL,0);
	printf("end process\n");
	return 0;
}