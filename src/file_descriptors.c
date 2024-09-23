/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:43:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/23 18:24:06 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_rdin_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		manage_error("Error: Set_rdin_fd.");
		return ;
	}
	cmd->in_rd->fd = fd;
}

void	set_rdout_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		manage_error("Error: Set_rdout_fd.");
		return ;
	}
	cmd->out_rd->fd = fd;
}

void	set_append_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		manage_error("Error: Set_append_fd.");
		return ;
	}
	cmd->out_rd->fd = fd;
}

void	set_herdoc_fd(t_cmd *cmd, char *path)
{
	
}

void	set_file_descriptor(t_cmd *cmd, char *path, t_tkn_type type)
{
	void	(*set_fd[4])(t_cmd *cmd, char *path);

	set_fd[0] = set_rdin_fd;
	set_fd[1] = set_rdout_fd;
	set_fd[2] = set_append_fd;
	set_fd[3] = set_herdoc_fd;
	set_fd[type - 2](cmd, path);
}
