/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:25 by jpancorb          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/11 13:28:46 by apaterno         ###   ########.fr       */
=======
/*   Updated: 2024/10/29 18:45:53 by jpancorb         ###   ########.fr       */
>>>>>>> export_v2
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->full_path = NULL;
	cmd->in_rd = NULL;
	cmd->out_rd = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->built_in = NULL;
	return (cmd);
}

t_red	*create_red_node(char *file, int type)
{
	t_red	*red;

	red = (t_red *)malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->file = file;
	red->type = type;
	red->next = NULL;
	red->fd = 0;
	return (red);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = count_args(cmd->args);
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

t_cmd	*add_pipe(t_cmd *curr)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd_node();
	if (!new_cmd)
		return (NULL);
	curr->next = new_cmd;
	new_cmd->prev = curr;
	return (new_cmd);
}
