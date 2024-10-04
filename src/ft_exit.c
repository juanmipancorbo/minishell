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

int	ft_exit(t_cmd *cmd, t_utils *utils)
{
	(void)cmd;
	(void)utils;
	printf("exit\n");
	return (EXIT_SUCCESS);
}
