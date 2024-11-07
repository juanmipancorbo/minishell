/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:59:29 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/06 19:04:10 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_red(t_cmd *cmd, char *file, int type)
{
	t_red	*red;

	red = create_red_node(file, type);
	if (!red)
		return ;
	if (type == RD_IN)
		add_in_red(cmd, red);
	else if (type == HEREDOC)
	{
		red->herecoc_f = new_heredoc_filename();
		add_in_red(cmd, red);
	}
	else if (type == RD_OUT || type == APPEND)
		add_out_red(cmd, red);
}

void	full_path_to_arg(t_cmd	*cmd)
{
	if (cmd->full_path)
	{
		free(cmd->args[0]);
		cmd->args[0] = ft_strdup(cmd->full_path);
	}
}

void	free_redirections(t_red *red)
{
	t_red	*temp;

	while (red)
	{
		temp = red;
		red = red->next;
		if (temp->herecoc_f != NULL)
			delete_herdocf(temp->herecoc_f);
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
		i = 0;
		temp = cmds;
		cmds = cmds->next;
		if (!temp->args)
		{
			free_cmds_more(temp);
			return ;
		} 
		while (temp->args[i])
		{
			free(temp->args[i]);
			i++;
		}
		free(temp->args);
		temp->args = NULL;
		free_cmds_more(temp);
	}
}
