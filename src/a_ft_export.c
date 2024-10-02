/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:20 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:20 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_export(t_cmd *cmd, t_utils *utils)
{
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("export\n");
	return (EXIT_SUCCESS);
}
