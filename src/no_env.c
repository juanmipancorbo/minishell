/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:56:21 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/30 20:48:35 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	to_no_env(t_utils *utils)
{
	int		i;
	char	*pwd;
	char	**env_min;

	i = -1;
	env_min = (char **)malloc(sizeof(char *) * 7);
	if (!env_min)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = strdup("/home");
	env_min[0] = malloc(strlen("PWD=") + strlen(pwd) + 1);
	strcpy(env_min[0], "PWD=");
	strcat(env_min[0], pwd);
	env_min[1] = strdup("LS_COLORS=");
	env_min[2] = strdup("LESSCLOSE=/usr/bin/lesspipe %s %s");
	env_min[3] = strdup("LESSOPEN=| /usr/bin/lesspipe %s");
	env_min[4] = strdup("SHLVL=1");
	env_min[5] = strdup("_=/usr/bin/env");
	env_min[6] = NULL;
	while (++i < 6)
		if (!env_min[i])
			break ;
	utils->env_var = env_min;
	free(pwd);
}

