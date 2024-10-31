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
	{
		dup2(out_node->fd, STDOUT_FILENO);
		close(out_node->fd);
	}
	if (in_node != NULL)
	{
		dup2(in_node->fd, STDIN_FILENO);
		close(in_node->fd);
	}
}

static void	exec_builtin(t_cmd *cmd, t_utils *utils, int **pipes_fd, int cmd_id)
{
	pid_t	child;

	if (is_forked(cmd))
	{
		child = fork();
		if (child == -1)
			manage_error(ERROR);
		if (child == 0)
		{
			set_pipes_fd(cmd, cmd_id, pipes_fd, child);
			set_fd_redirections(cmd);
			cmd->built_in(cmd, utils);
			exit(EXIT_SUCCESS);
		}
		else
		{
			set_pipes_fd(cmd, cmd_id, pipes_fd, child);
			close_fd_redlst(cmd);
			waitpid(child, NULL, 0);
		}
	}
	else
	{
		cmd->built_in(cmd, utils);
	}
}

static void	exec_cmd(t_cmd *cmd, t_utils *utils, int **pipes_fd, int cmd_id)
{
	if (!fill_fd(cmd))
			return;
	utils->process_id[cmd_id] = fork();
	if (utils->process_id[cmd_id] == -1)
		manage_error(ERROR);
	if (utils->process_id[cmd_id] == 0)
	{
		check_cmd_access(cmd);
		set_pipes_fd(cmd, cmd_id, pipes_fd, utils->process_id[cmd_id]);
		set_fd_redirections(cmd);
		if (execve(cmd->full_path, cmd->args, utils->env_var) != 0)
			manage_error(ERROR);
	}
	else
		set_pipes_fd(cmd, cmd_id, pipes_fd, utils->process_id[cmd_id]);
}

void	init_execution(t_cmd **command, t_utils *utils)
{
	int		cmd_id;
	int		**pipes_fd;
	t_cmd	*cmd;

	g_exit_code = 0;
	cmd = *command;
	cmd_id = 0;
	pipes_fd = create_pipes_fd(cmd_lst_size(command));
	utils->process_id = get_pid_array(cmd_lst_size(command));
	init_signals(0);
	while (cmd != NULL)
	{
		if (cmd->built_in != NULL)
			exec_builtin(cmd, utils, pipes_fd, cmd_id);
		else
			exec_cmd(cmd, utils, pipes_fd, cmd_id);
		close_fd_redlst(cmd);
		cmd_id++;
		cmd = cmd->next;
	}
	wait_process(utils, cmd_lst_size(command));
}
