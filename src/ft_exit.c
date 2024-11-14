/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:02:23 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/04 17:02:23 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[1] == '\0')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_utils *utils)
{
	int	exit_code;

	if (!utils->is_pipe)
		printf("exit\n");
	if (cmd->args[1])
	{
		if (!is_num_str(cmd->args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			exit_code = 2;
		}
		else if (cmd->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		else
			exit_code = ft_atoi(cmd->args[1]);
	}
	else
		exit_code = 0;
	free_env_copy(utils);
	exit(exit_code);
	return (0);
}
