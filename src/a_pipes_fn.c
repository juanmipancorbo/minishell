/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pipes_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:51:17 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/20 16:51:17 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	**create_pipes_fd(int cmd_nb)
{
	int	**pipe_fd;
	int	i;
	int	pipes_nb;

	if (cmd_nb == 0 || cmd_nb == 1)
		return (0);
	pipes_nb = cmd_nb - 1;
	pipe_fd = malloc(sizeof(int *) * pipes_nb);
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
	while (i < pipes_nb)
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
		
	}
	else
		
}

static void end_cmd_pipe(t_cmd *cmd, int cmd_id, int **pipes_fd, pid_t pid)
{
	if (pid == 0)
	{
		dup2(pipes_fd[cmd_id - 1][READ_END], STDOUT_FILENO);
		close(pipes_fd[cmd_id - 1][READ_END]);
	}
	else
		close(pipes_fd[cmd_id - 1][READ_END]);
}


void set_pipes_fd(t_cmd *cmd, int cmd_id , int **pipes_fd , pid_t pid)
{
	int i;

	if (pipes_fd == 0)
		return;

	if(cmd->prev == NULL)
		init_cmd_pipe(cmd, cmd_id, pipes_fd, pid);
	if(cmd->next == NULL)
		end_cmd_pipe(cmd,cmd_id,pipes_fd,pid);
	else;
}

