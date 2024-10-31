/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:36 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/31 17:58:18 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void check_cmd_access(t_cmd *cmd)
{
	if (access(cmd->full_path, F_OK))
		cmd_error(ft_strjoin(cmd->args[0],": command not found\n"),127);
	if (access(cmd->full_path, X_OK))
		cmd_error(ft_strjoin(cmd->args[0],": Permission denied\n"),126);;
}		

void	wait_process(t_utils *utils, int nb_process)
{
	int status;
	int i;

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
		//printf("EXIT\n");
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exit_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_exit_code = 131;
	}
	init_signals(1);
	// 	else if (WIFSTOPPED(status))
	// 	printf("%d\n",WSTOPSIG(status));
	// else
	// 	printf("+%d\n",WTERMSIG(status));
		
}