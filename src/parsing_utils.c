/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:59:29 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/26 18:18:15 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_red(t_cmd *cmd, char *file, int type)
{
	t_red	*red;

	/// agregar file descriptor //
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
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->full_path)
			free(temp->full_path);
		if (temp->in_rd)
			free_redirections(temp->in_rd);
		if (temp->out_rd)
			free_redirections(temp->out_rd);
		free(temp);
	}
}

void	free_q(t_token **curr, t_token **end)
{
	*end = *curr;
	*curr = (*curr)->next;
	free((*end)->value);
	free(*end);
}
