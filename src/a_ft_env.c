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

int	ft_env(t_cmd *cmd, t_utils *utils)
{
	int	i;

	if (cmd->args[1])
	{
		ft_putendl_fd("Error : wrong number of arguments", 2);
		return (1);
	}
	i = 0;
	while (utils->env_var[i])
	{
		ft_putendl_fd(utils->env_var[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
