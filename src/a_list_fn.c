/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_list_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:40:14 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/10 12:40:14 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_red	*red_last_node(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_fdnode_back(t_red **lst, t_red *new)
{
	t_red	*back;

	back = red_last_node(*lst);
	if (!back)
		*lst = new;
	else
		back->next = new;
}

t_red	*create_fd_node(char *path, int fd)
{
	t_red	*new_node;

	new_node = malloc(sizeof(t_red));
	if (!new_node)
		exit_error(MALLOC_E, 10);
	new_node->file = path;
	new_node->fd = fd;
	return (new_node);
}

int	redlst_size(t_red *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	close_fd_redlst(t_cmd *cmd)
{
	t_red	*in;
	t_red	*out;

	in = cmd->in_rd;
	out = cmd->out_rd;
	while (in != NULL)
	{
		if (in->fd > 0)
			close(in->fd);
		in = in->next;
	}
	while (out != NULL)
	{
		if (out->fd > 0)
			close(out->fd);
		out = out->next;
	}
}
