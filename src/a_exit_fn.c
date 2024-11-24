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

void free_hd(int **pipes_fd, t_cmd **cmd, t_utils *utils)
{
	free(utils->process_id);
	free_pipes(pipes_fd, cmd_lst_size(cmd) - 1);
}