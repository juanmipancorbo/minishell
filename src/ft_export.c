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
	while (utils->export_var[++i])
		printf("declare -x %s\n", utils->export_var[i]);
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

static void	to_env_var(char *arg, char **env)
{
	char	*var_name;
	char	*value;

	if (!is_valid_identifier(arg) || arg[0] == '=' || arg[0] == '$')
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return ;
	}
	var_name = ft_strdup(arg);
	value = ft_strchr(var_name, '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	else
		return (free(var_name));
	if (replace_env_var(var_name, value, env))
		add_env_var(var_name, value, env);
	free(var_name);
}

int	ft_export(t_cmd *cmd, t_utils *utils)
{
	int		i;

	if (utils->env_var)
		dup_env_variables(utils, NULL, utils->env_var, &utils->export_var);
	if (!cmd->args[1])
		return (print_env_var(utils));
	i = 0;
	while (cmd->args[++i])
	{
		// to_env_var(cmd->args[i], utils->export_var);
		to_env_var(cmd->args[i], utils->env_var);
	}
	return (0);
}
