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

static t_red	*last_node(t_red *lst)
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

	back = last_node(*lst);
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
		manage_error(MALLOC_E);
	new_node->name = path;
	new_node->fd = fd;
}
