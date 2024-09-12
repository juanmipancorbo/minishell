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

static void set_fd_redirections(t_cmd *cmd)
{
	if (redlst_size(cmd->out_rd) > 0)
		dup2(cmd->out_rd->fd, STDOUT_FILENO);
	if (redlst_size(cmd->in_rd) > 0)
		dup2(cmd->in_rd->fd, STDIN_FILENO);
	return;
}

static void execute_command(t_cmd *command, t_utils *utils)
{
	pid_t child;

	if ((child = fork()) == -1)
		manage_error(ERROR);
	if (child == 0)
	{
		execve(command->full_path,command->args,utils->env_var);
	}
	wait(NULL);
}

void	init_execution(t_cmd *command, t_utils *utils)
{
		set_fd_redirections(command);
		execute_command(command, utils);
}
