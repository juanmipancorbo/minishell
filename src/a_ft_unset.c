/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:35 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:35 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_unset(t_cmd *cmd, t_utils *utils)
{
	(void)utils;
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("unset\n");
	return (EXIT_SUCCESS);
}
