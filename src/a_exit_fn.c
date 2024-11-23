/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exit_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:22:09 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/20 16:22:09 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	check_files(char *path)
{
	return (access(path, F_OK));
}

void	delete_herdocf(char *heredocf)
{
	unlink(heredocf);
	free(heredocf);
}

void	error_msg(char *msg, int exit_code)
{
	ft_putendl_fd(msg, 2);
	g_exit_code = exit_code;
}
void	error_msg_free(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	free(msg);
	g_exit_code = exit_code;
}