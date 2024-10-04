/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:59:29 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/04 17:16:16 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_red(t_cmd *cmd, char *file, int type)
{
	t_red	*red;

	red = create_red_node(file, type);
	if (!red)
		return ;
	if (type == RD_IN || type == HEREDOC)
		add_in_red(cmd, red);
	else if (type == RD_OUT || type == APPEND)
		add_out_red(cmd, red);
}

void	full_path_to_arg(t_cmd	*cmd)
{
	if (cmd->full_path)
		cmd->args[0] = ft_strdup(cmd->full_path);
}

void	free_redirections(t_red *red)
{
	t_red	*temp;

	while (red)
	{
		temp = red;
		red = red->next;
		free(temp);
	}
}

static void	free_cmds_more(t_cmd *cmd)
{
	if (cmd->full_path)
		free(cmd->full_path);
	if (cmd->in_rd)
		free_redirections(cmd->in_rd);
	if (cmd->out_rd)
		free_redirections(cmd->out_rd);
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	int		i;

	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		if (temp->args)
		{
			i = 0;
			if (!temp->built_in)
			{
				free(temp->args[i]);
				// printf("Free args[%d].\n", i);
				i++;
			}
			free(temp->args);
		}
		free_cmds_more(temp);
	}
}
