/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:38:33 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/03 17:38:33 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	manage_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	file_error(char *msg)
{
	perror(msg);
	free(msg);
	//exit(EXIT_FAILURE);
	//g_exit_code = 1;
}
