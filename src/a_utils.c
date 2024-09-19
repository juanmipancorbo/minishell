#include "../include/minishell.h"
t_cmd	*dlst_lastnode(t_cmd **cmd);
t_cmd	*dlst_lastnode(t_cmd **cmd);

int	cmd_lst_size(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	if (cmd == NULL)
		return (0);
	tmp = *cmd;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
////////////////

t_cmd	*cmd_addnewnode(char **argv , char *full_path)
{
	t_cmd	*node;

    node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = argv;
	node->full_path = full_path;
	node->in_rd = NULL;
	node->out_rd = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	dlstadd_back(t_cmd **cmd, t_cmd *node)
{
	t_cmd	*tmp;
	t_cmd	*lastnode;

	if (cmd == NULL)
		return ;
	tmp = *cmd;
	if (!tmp)
		*cmd = node;
	else
	{
		lastnode = dlst_lastnode(cmd);
		lastnode->next = node;
		node->prev = lastnode;
	}
}

t_cmd	*dlst_lastnode(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (cmd == NULL)
		return (NULL);
	tmp = *cmd;
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}