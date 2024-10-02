/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:27 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:27 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_pwd(t_cmd *cmd, t_utils *utils)
{
	(void)utils;
	write(1, cmd->args[0], ft_strlen(cmd->args[0]));
	return (EXIT_SUCCESS);
}
