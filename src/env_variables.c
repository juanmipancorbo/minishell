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

void	parse_pid(t_utils *utils, char *buffer)
{
	int		i;
	char	temp[12];

	i = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9' && i < 11)
	{
		temp[i] = buffer[i];
		i++;
	}
	temp[i] = '\0';
	utils->pid = malloc(sizeof(char) * (i + 1));
	if (!utils->pid)
		ft_putendl_fd("Malloc error: parse_pid.", STDERR_FILENO);
	utils->process_id = NULL;
	ft_strlcpy(utils->pid, temp, ft_strlen(temp));
}

void	dup_env_variables(t_utils *utils, int pid, char **from, char ***to)
{
	int		i;
	char	**new_env;

	i = 0;
	while (from[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		exit_error(MALLOC_E, 10);
	i = 0;
	while (from[i])
	{
		new_env[i] = ft_strdup(from[i]);
		if (!new_env[i])
			exit_error(MALLOC_E, 10);
		i++;
	}
	new_env[i] = NULL;
	*to = new_env;
	if (pid)
	{
		to_get_pid(utils);
		utils->export_var = NULL;
	}
	update_shlvl(utils);
}

int	replace_env_var(char *var_name, char *new_value, char **env)
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
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var_name, var_len))
		{
			free(env[i]);
			env[i] = new_var;
			return (0);
		}
		i++;
	}
	free(new_var);
	return (-1);
}

char	*new_var_entry(char *var_name, char *value)
{
	char	*new_var;

	if (value)
	{
		new_var = ft_strjoin(var_name, "=");
		if (!new_var)
			return (NULL);
		new_var = ft_strjoin_free(new_var, value);
		if (!new_var)
			return (NULL);
	}
	else
	{
		new_var = ft_strdup(var_name);
		if (!new_var)
			return (NULL);
	}
	return (new_var);
}

void	add_env_var(char *var_name, char *value, char ***env)
{
	char	**new_env;
	char	*new_var;
	int		i;

	new_var = new_var_entry(var_name, value);
	if (!new_var)
		return ;
	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}
