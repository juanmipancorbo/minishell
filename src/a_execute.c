/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:54 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/03 13:10:54 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

static void	set_fd_redirections(t_cmd *cmd)
{
	t_red	*in_node;
	t_red	*out_node;

	in_node = red_last_node(cmd->in_rd);
	out_node = red_last_node(cmd->out_rd);
	if (out_node != NULL)
		dup2(out_node->fd, STDOUT_FILENO);
	if (in_node != NULL)
		dup2(in_node->fd, STDIN_FILENO);
}

static void	execute_command(t_cmd *cmd, t_utils *utils, int **pipe_fd, int cmd_id)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		manage_error(ERROR);
	if (child == 0)
	{
		if (cmd_id == 0)
		{
			close(pipe_fd[cmd_id][READ_END]);

			dup2(pipe_fd[cmd_id][WRITE_END], STDOUT_FILENO);
			close(pipe_fd[cmd_id][WRITE_END]);
			if(execve(cmd->full_path, cmd->args, utils->env_var) != 0)
				manage_error(ERROR);
		}
		else
		{
			dup2(pipe_fd[cmd_id - 1][READ_END], STDIN_FILENO);
			close(pipe_fd[cmd_id - 1][READ_END]);
			if(execve(cmd->full_path, cmd->args, utils->env_var) != 0)
				manage_error(ERROR);
		}
	}
	else
	{
		if (cmd_id == 0)
		{
			close(pipe_fd[cmd_id][WRITE_END]);
			waitpid(child,NULL,0);
		}
		else
		{
			close(pipe_fd[cmd_id - 1][READ_END]);
			waitpid(child,NULL,0);
		}	
	}
}

void	init_execution(t_cmd **command, t_utils *utils)
{
	int cmd_id;
	int **pipes_fd;
	t_cmd *cmd;

	cmd = *command;
	cmd_id = 0;
	pipes_fd = create_pipes_fd(cmd_lst_size(command));

	while (cmd != NULL)
	{
		execute_command(cmd, utils, pipes_fd, cmd_id); 
		//set_pipes_fd(cmd, cmd_id, pipes_fd, 0);
		cmd_id++;
		cmd = cmd->next;
	}
	printf("fin proceso\n");
	// funcion limpiar fd
	//clean_exit(command);
}
