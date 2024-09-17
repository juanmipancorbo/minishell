#include "../include/minishell.h"

int execute(int i, int *fd)
{
	pid_t child;

	
	child = fork();
	if (child == 0)
	{
		printf("loop %i\n", i);
		if(i == 0)
		{
			close(fd[READ_END]);
			dup2(fd[WRITE_END],STDOUT_FILENO);
			close(fd[WRITE_END]);
			execlp("ls","-a",NULL);
		}
		else
		{
			close(fd[WRITE_END]);
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[READ_END]);
			execlp("wc","-c",NULL);
		}
	}
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	return child;

}
int main(void)
{
	int i = 0;
	int pipe_fd[2];
	
	pipe(pipe_fd);
	while (i < 2)
	{
		waitpid(execute(i, pipe_fd),NULL,0);
		i++;
	}
	printf("End\n");
}