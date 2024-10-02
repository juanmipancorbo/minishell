/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:13 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:13 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_exit(t_cmd *cmd, t_utils *utils)
{
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
