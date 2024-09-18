#include "../include/minishell.h"

int main(void)
{
	char *arg1[3]={"/bin/ls", "-l", NULL};
	char *arg2[3]={"/bin/grep", "pipe", NULL};
	char *arg3[3]={"/bin/wc", "-l", NULL};
	int pipe_fd[2][2];
	pid_t pid[3];
	int x;
	char buff[1025];

	pipe(pipe_fd[0]);
	pipe(pipe_fd[1]);

	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipe_fd[1][READ_END]);
		close(pipe_fd[1][WRITE_END]);
		//
		close(pipe_fd[0][READ_END]);
		dup2(pipe_fd[0][WRITE_END], STDOUT_FILENO);
		close(pipe_fd[0][WRITE_END]);
		execv(arg1[0],arg1);
	}
	else
	{
		// cerar files descriptor
		close(pipe_fd[0][WRITE_END]);


		pid[1] = fork();
		
		if(pid[1] == 0)
		{
			close(pipe_fd[1][READ_END]);
			dup2(pipe_fd[0][READ_END], STDIN_FILENO);
			close(pipe_fd[0][READ_END]);

			dup2(pipe_fd[1][WRITE_END],STDOUT_FILENO);
			close(pipe_fd[1][WRITE_END]);
			execv(arg2[0],arg2);
		}
		else
		{
			close(pipe_fd[0][READ_END]);
			close(pipe_fd[1][WRITE_END]);
			pid[2] = fork();
			if (pid[2] == 0)
			{
				dup2(pipe_fd[1][READ_END],STDIN_FILENO);
				close(pipe_fd[1][READ_END]);
				execv(arg3[0],arg3);
			}
			else
				close(pipe_fd[1][READ_END]);
		}
	waitpid(pid[0],NULL,0);
	waitpid(pid[1],NULL,0);
	waitpid(pid[2],NULL,0);
	}
	
}