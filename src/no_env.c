/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:56:21 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/06 18:42:27 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
}


void	to_no_env(t_utils *utils)
{
	int		i;
	char	*pwd;
	char	**env_min;
	size_t	pwd_len;

	i = -1;
	env_min = (char **)malloc(sizeof(char *) * 2);
	if (!env_min)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/home");
	pwd_len = ft_strlen("PWD=") + ft_strlen(pwd) + 1;
	env_min[0] = malloc(pwd_len);
	ft_strcpy(env_min[0], "PWD=");
	ft_strlcat(env_min[0], pwd, pwd_len);
	env_min[1] = NULL;
	while (++i < 1)
		if (!env_min[i])
			break ;
	utils->env_var = env_min;
	update_shlvl(utils);
	free(pwd);
}

