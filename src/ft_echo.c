/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:42:44 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/01 17:42:44 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_cmd *cmd, t_utils *utils)
{
	int	i;
	int	newline;

	(void)utils;
	i = 1;
	newline = 1;
	if (cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 3))
	{
		newline = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		// if (cmd->args[i + 1])
		// 	write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
