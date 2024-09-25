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

static void	exec_cmd(t_cmd *cmd, t_utils *utils, int **pipes_fd, int cmd_id)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		manage_error(ERROR);
	if (child == 0)
	{
		set_pipes_fd(cmd, cmd_id, pipes_fd, child);
		set_fd_redirections(cmd);
		if (execve(cmd->full_path, cmd->args, utils->env_var) != 0)
			manage_error(ERROR);
	}
	else
	{
		set_pipes_fd(cmd, cmd_id, pipes_fd, child);
		close_fd_redlst(cmd);
		waitpid(child, NULL, 0);
	}
}

void	init_execution(t_cmd **command, t_utils *utils)
{
	int		cmd_id;
	int		**pipes_fd;
	t_cmd	*cmd;

	cmd = *command;
	cmd_id = 0;
	pipes_fd = create_pipes_fd(cmd_lst_size(command));
	while (cmd != NULL)
	{
		exec_cmd(cmd, utils, pipes_fd, cmd_id);
		cmd_id++;
		cmd = cmd->next;
	}
	// funcion limpiar fd
	//clean_exit(command);
}
