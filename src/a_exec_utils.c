/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:36 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/28 18:01:20 by apaterno         ###   ########.fr       */
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