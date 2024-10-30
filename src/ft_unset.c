/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:03:05 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/30 18:03:05 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_env_list(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
		free(env_list[i++]);
	free(env_list);
}

int	to_env_list_size(char **env_list)
{
	int	size;

	size = 0;
	while (env_list[size])
		size++;
	return (size);
}

static char	**create_new_list(char **old_list, int index)
{
	int		i;
	int		j;
	char	**new_list;

	new_list = (char **)malloc(sizeof(char *) * to_env_list_size(old_list));
	if (!new_list)
		return (NULL);
	i = 0;
	j = 0;
	while (old_list[i])
	{
		if (i != index)
		{
			new_list[j] = ft_strdup(old_list[i]);
			if (!new_list[j++])
			{
				free_env_list(new_list);
				return (NULL);
			}
		}
		i++;
	}
	new_list[j] = NULL;
	return (new_list);
}

static int	remove_var_from_list(char *var_name, char ***var_list)
{
	int		i;
	int		len;
	char	**new_list;
	char	**old_list;

	old_list = *var_list;
	len = ft_strlen(var_name);
	i = 0;
	while (old_list[i])
	{
		if (ft_strncmp(old_list[i], var_name, len) == 0
			&& (old_list[i][len] == '=' || old_list[i][len] == '\0'))
		{
			new_list = create_new_list(old_list, i);
			if (!new_list)
				return (-1);
			*var_list = new_list;
			free(old_list);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_utils *utils)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (cmd->args[i])
	{
		if (remove_var_from_list(cmd->args[i], &utils->env_var) == -1)
			result = -1;
		if (remove_var_from_list(cmd->args[i], &utils->export_var) == -1)
			result = -1;
		i++;
	}
	return (result);
}
