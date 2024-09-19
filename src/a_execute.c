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

static void	execute_command(t_cmd *command, t_utils *utils)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		manage_error(ERROR);
	if (child == 0)
	{
		set_fd_redirections(command);
		execve(command->full_path, command->args, utils->env_var);
	}
	wait(NULL);
}

void	init_execution(t_cmd *command, t_utils *utils)
{
	execute_command(command, utils);
	clean_exit(command);
}
