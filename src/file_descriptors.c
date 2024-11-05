/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:36:35 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/10 12:36:35 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	set_rdin_fd(t_red *red)
{
	int	fd;

	fd = open(red->file, O_RDONLY);
	if (fd < 0)
	{
		file_error(ft_strjoin("-Minishell: ", red->file), 1);
		return (FALSE);
	}
	red->fd = fd;
	return (TRUE);
}

static t_bool	set_rdout_fd(t_red *red)
{
	int	fd;

	fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		file_error(ft_strjoin("-Minishell: ", red->file), 1);
		return (FALSE);
	}
	red->fd = fd;
	return (TRUE);
}

static t_bool	set_append_fd(t_red *red)
{
	int	fd;

	fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		file_error(ft_strjoin("-Minishell: ", red->file), 1);
		return (FALSE);
	}
	red->fd = fd;
	return (TRUE);
}

static t_bool	set_heredoc_fd(t_red *red)
{
	int	fd;

	// if (!read_loop(red->file))
	// 	return (FALSE);
	init_signals(1);
	fd = open(HEREDOC_F, O_RDONLY);
	if (fd < 0)
	{
		file_error(ft_strjoin("-Minishell: ", HEREDOC_F), 1);
		return (FALSE);
	}
	red->fd = fd;
	return (TRUE);
}

t_bool	set_file_descriptor(t_red *red)
{
	t_bool (*set_fd[4])(t_red * red);
	set_fd[0] = set_rdin_fd;
	set_fd[1] = set_rdout_fd;
	set_fd[2] = set_append_fd;
	set_fd[3] = set_heredoc_fd;
	if (set_fd[red->type - 2](red))
		return (TRUE);
	return (FALSE);
}
