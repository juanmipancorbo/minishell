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

static int	print_env_var(t_utils *utils)
{
	int		i;

	i = -1;
	while (utils->env_var[++i])
		printf("declare -x %s\n", utils->env_var[i]);
	return (0);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || ft_isdigit(str[0]))
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

// static void	to_export_var(char *arg, t_utils *utils)
// {
// 	char	*value;

// 	value = ft_strdup(arg);
// 	is (value[0] == )
// }

static void	to_env_var(char *arg, t_utils *utils)
{
	char	*var_name;
	char	*value;

	var_name = ft_strdup(arg);
	value = ft_strchr(var_name, '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	else
		return (free(var_name));
	if (!is_valid_identifier(var_name) || *arg == '=' || *arg == '$')
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return (free(var_name));
	}
	if (replace_env_var(var_name, value, utils))
		add_env_var(var_name, value, utils);
	free(var_name);
}

int	ft_export(t_cmd *cmd, t_utils *utils)
{
	int		i;

	if (!cmd->args[1])
		return (print_env_var(utils));
	i = 0;
	while (cmd->args[++i])
	{
		// to_export_var(cmd->args[i], utils);
		to_env_var(cmd->args[i], utils);
	}
	return (0);
}
