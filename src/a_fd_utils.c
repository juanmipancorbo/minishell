/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_fd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:36:35 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/10 12:36:35 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_rdin_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	add_fdnode_back(&cmd->in_rd, create_fd_node(path, fd));
}

// falta terminar //
static void	set_herdoc_fd(t_cmd *cmd, char *path)
{
	int	fd;

	(void)fd;
	(void)cmd;
	(void)path;
}

static void	set_rdout_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	add_fdnode_back(&cmd->out_rd, create_fd_node(path, fd));
}

static void	set_append_fd(t_cmd *cmd, char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);
	add_fdnode_back(&cmd->out_rd, create_fd_node(path, fd));
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
