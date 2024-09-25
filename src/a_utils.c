#include "../include/minishell.h"

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
