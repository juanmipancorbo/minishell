/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:36 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/20 18:12:59 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_directory(char *path)
{
	struct stat	file_stat;

	stat(path, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

void	check_cmd_access(t_cmd *cmd)
{
	// modificado juan
	if (!cmd->args)
		return ;
	if (cmd->full_path == NULL)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			file_error(ft_strjoin("minishell: ", cmd->args[0]), 127);
			exit(127);
		}
		else
			cmd_error(ft_strjoin(cmd->args[0], ": command not found\n"), 127);
	}
	if (is_directory(cmd->full_path))
		cmd_error(ft_strjoin(cmd->args[0], ": Is a directory\n"), 126);
	if (access(cmd->full_path, F_OK))
	{
		file_error(ft_strjoin("minishell: ", cmd->full_path), 127);
		exit(127);
	}
	if (access(cmd->full_path, X_OK))
		cmd_error(ft_strjoin(cmd->args[0], ": Permission denied\n"), 126);
}

void	wait_process(t_utils *utils, int nb_process)
{
	int	status;
	int	i;

	i = 0;
	status = -1;
	while (i < nb_process)
	{
		waitpid(utils->process_id[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		g_exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exit_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_exit_code = 131;
	}
	init_signals(1);
	free(utils->process_id);
	utils->process_id = NULL;
}
