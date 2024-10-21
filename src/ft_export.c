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

static int	print_export_var(t_utils *utils)
{
	int		i;

	i = -1;
	while (utils->export_var[++i])
		printf("declare -x %s\n", utils->export_var[i]);
	return (0);
}

static int	check_new_var(char *var_name)
{
	int	i;

	i = -1;
	if (ft_isdigit(var_name[0]) || var_name[0] == '=' || var_name[0] == '$')
		return (-1);
	while (var_name[++i])
	{
		if (ft_isalnum(var_name[i]))
			continue ;
		if (var_name[i] == '_' || var_name[i] == '=')
			continue ;
		else
		{
			printf("ojete BORAZZZZZ\n");
			return (-1);
		}
	}
	return (0);
}

static int	check_var_name(char *var_name)
{
	while (*var_name)
	{
		if (!ft_isalnum(*var_name) && *var_name != '_')
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				*var_name);
			return (-1);
		}
		var_name++;
	}
	return (0);
}

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
		if (!*value)
			value = "";
		if (check_var_name(var_name))
			return ;
		if (replace_env_var(var_name, value, utils->env_var))
		{
			add_env_var(var_name, value, utils->export_var);
			add_env_var(var_name, value, utils->env_var);
			printf("MANIANAAAAAAAAAA\n");
		}
		else
			replace_env_var(var_name, value, utils->export_var);
	}
	else
		if (check_var_name(var_name))
			add_env_var(var_name, NULL, utils->export_var);
	free(var_name);
}

int	ft_export(t_cmd *cmd, t_utils *utils)
{
	int		i;

	if (utils->env_var && !utils->export_var)
		dup_env_variables(utils, NULL, utils->env_var, &utils->export_var);
	if (!cmd->args[1])
		return (print_export_var(utils));
	i = 0;
	while (cmd->args[++i])
	{
		// to_env_var(cmd->args[i], &utils->export_var);
		if (!check_new_var(cmd->args[i]))
			to_env_var(cmd->args[i], utils);
	}
	return (0);
}
