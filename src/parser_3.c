/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:05:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/19 21:14:51 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_in_red(t_cmd *cmd, t_red *red)
{
	t_red	*temp;

	if (!cmd->in_rd)
		cmd->in_rd = red;
	else
	{
		temp = cmd->in_rd;
		while (temp->next)
			temp = temp->next;
		temp->next = red;
	}
}

void	add_out_red(t_cmd *cmd, t_red *red)
{
	t_red	*temp;

	if (!cmd->out_rd)
		cmd->out_rd = red;
	else
	{
		temp = cmd->out_rd;
		while (temp->next)
			temp = temp->next;
		temp->next = red;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_env_value(char **env, const char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*full_path;
	int		len_path;
	int		len_cmd;

	len_path = ft_strlen(path);
	len_cmd = ft_strlen(cmd);
	full_path = malloc(len_path + len_cmd + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	full_path[len_path] = '/';
	ft_strcpy(full_path + len_path + 1, cmd);
	return (full_path);
}
