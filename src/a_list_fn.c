#include "../include/minishell.h"

static t_red	*last_node(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_fdNode_back(t_red **lst, t_red *new)
{
	t_red	*back;

	back = last_node(*lst);
	if (!back)
		*lst = new;
	else
		back->next = new;
}


t_red *create_fd_node(t_cmd *cmd, char *path, int fd)
{
	t_red *new_node;

	new_node = malloc(sizeof(t_red));
		if(!new_node)
			manage_error(MALLOC_E);
	new_node->name = path;
	new_node->fd = fd;
}

