/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:42:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/04 17:42:39 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_utils *utils)
{
	char	*var_name;
	char	*value;
	int		i;

	if (!cmd->args[1])
	{
		i = 0;
		while (utils->env_var[i])
		{
			printf("declare -x %s\n", utils->env_var[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		var_name = ft_strdup(cmd->args[i]);
		value = ft_strchr(var_name, '=');
		if (value)
		{
			*value = '\0';
			value++;
		}
		else
			value = "";
		if (!is_valid_identifier(var_name))
		{
			printf("bash: export: `%s': not a valid identifier\n",
				cmd->args[i]);
			free(var_name);
			return (1);
		}
		else
			replace_env_var(var_name, value, utils);
		free(var_name);
		i++;
	}
	return (0);
}
