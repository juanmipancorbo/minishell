/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:07:01 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/07 20:07:01 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_env_variables(t_utils *utils, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		manage_error(MALLOC_E);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			manage_error(MALLOC_E);
		i++;
	}
	new_env[i] = NULL;
	utils->env_var = new_env;
}

int	replace_env_var(char *var_name, char *new_value, t_utils *utils)
{
	int		i;
	char	*new_var;
	size_t	var_len;

	var_len = ft_strlen(var_name);
	new_var = ft_strjoin(var_name, "=");
	if (!new_var)
		return (-1);
	new_var = ft_strjoin_free(new_var, new_value);
	if (!new_var)
		return (-1);
	i = 0;
	while (utils->env_var[i])
	{
		if (!ft_strncmp(utils->env_var[i], var_name, var_len)
			&& utils->env_var[i][var_len] == '=')
		{
			free(utils->env_var[i]);
			utils->env_var[i] = new_var;
			return (0);
		}
		i++;
	}
	free(new_var);
	return (-1);
}

void	add_env_var(char *var_name, char *value, t_utils *utils)
{
	char	**new_env_var;
	char	*new_var;
	int		i;

	new_var = ft_strjoin(var_name, "=");
	if (!new_var)
		return ;
	new_var = ft_strjoin_free(new_var, value);
	if (!new_var)
		return ;
	i = 0;
	while (utils->env_var[i])
		i++;
	new_env_var = malloc(sizeof(char *) * (i + 2));
	if (!new_env_var)
		return ;
	i = -1;
	while (utils->env_var[++i])
		new_env_var[i] = utils->env_var[i];
	new_env_var[i] = new_var;
	new_env_var[i + 1] = NULL;
	free(utils->env_var);
	utils->env_var = new_env_var;
}
