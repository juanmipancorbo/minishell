/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:17:58 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:17:58 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

static t_bool check_args(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (FALSE);
	if (is_directory(cmd->args[1]))
	{
		printf("minishell: %s : permission denied\n",cmd->args[1]);
		g_exit_code = 126;
		return(TRUE);
	}
	if (access(cmd->args[1], F_OK))
	{
		file_error(ft_strjoin("minishell: ", cmd->args[1]), 127);
		return (TRUE);
	}
	if (access(cmd->args[1], X_OK))
	{
		printf("minishell: %s : permission denied\n",cmd->args[1]);
		g_exit_code = 126;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_env(t_cmd *cmd, t_utils *utils)
{
	int	i;


	if(check_args(cmd))
		return (g_exit_code);
	i = 0;
	while (utils->env_var[i])
	{
		ft_putendl_fd(utils->env_var[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
