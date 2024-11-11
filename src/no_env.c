/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:56:21 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/11 19:58:46 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*to_last_argument(t_cmd *cmd)
{
	int		i;
	char	*last_arg;

	if (!cmd || !cmd->args)
		return (NULL);

	i = 0;
	last_arg = NULL;
	while (cmd->args[i] != NULL)
	{
		last_arg = cmd->args[i];
		i++;
	}
	return (last_arg);
}

void	update_shlvl(t_utils *utils)
{
	int		int_value;
	char	*ascii_value;

	ascii_value = getenv("SHLVL");
	if (ascii_value)
		int_value = ft_atoi(ascii_value) + 1;
	else
		int_value = 1;
	ascii_value = ft_itoa(int_value);
	if (!ascii_value)
		return ;
	if (replace_env_var("SHLVL", ascii_value, utils->env_var))
		add_env_var("SHLVL", ascii_value, &utils->env_var);
	free(ascii_value);
}


void	to_no_env(t_utils *utils)
{
	int		i;
	char	*pwd;
	char	**env_min;
	size_t	pwd_len;

	i = -1;
	env_min = (char **)malloc(sizeof(char *) * 3);
	if (!env_min)
		return ;
	pwd = getcwd(NULL, 0);
	pwd_len = ft_strlen("PWD=") + ft_strlen(pwd) + 1;
	env_min[0] = malloc(pwd_len);
	ft_strcpy(env_min[0], "PWD=");
	ft_strlcat(env_min[0], pwd, pwd_len);
	env_min[1] = ft_strdup("_=]");
	env_min[2] = NULL;
	while (++i < 2)
		if (!env_min[i])
			break ;
	utils->env_var = env_min;
	utils->export_var = NULL;
	utils->pid = NULL;
	update_shlvl(utils);
	free(pwd);
}
