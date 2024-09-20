#include "../include/minishell.h"

int	**create_pipes_fd(int np)
{
	int	**pipe_fd;
	int	i;
	int	pipes_nb;

	pipes_nb = np - 1;
	if (np == 0)
		return (0);
	pipe_fd = malloc(sizeof(int *) * pipe_nb);
	if (!pipe_fd)
		manage_error("ERROR");
	i = 0;
	while (i < pipes_nb)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			manage_error("ERROR");
		i++;
	}
	i = 0;
	while (i < np)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	return (pipe_fd);
}

static void init_cmd_pipe(t_cmd *cmd, int cmd_id, int **pipes_fd, pid_t pid)
{
	if (pid == 0)
	{
		close(pipe_fd[cmd_id][READ_END]);
		dup2(pipe_fd[cmd_id][WRITE_END], STDOUT_FILENO);
		close(pipe_fd[cmd_id][WRITE_END]);
		while (cmd->next->next != NULL)
		{
			cmd_id++;
			close(pipe_fd[cmd_id][READ_END]);
			close(pipe_fd[cmd_id][WRITE_END]);
			cmd = cmd->next;
		}
	}
	else
		close(pipe_fd[cmd_id][WRITE_END]);
}

void set_pipes_fd(t_cmd *cmd, int cmd_id , int **pipes_fd , pid_t pid)
{
	int i;

	if (pipes_fd == 0)
		return;

	if(cmd->prev == NULL)
	{

	}
	if(cmd->next == NULL)
	{

	}
	else
	{

	}
}

