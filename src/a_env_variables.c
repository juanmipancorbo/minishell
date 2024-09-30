/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_env_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:38 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/03 13:10:38 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_env_variables(t_utils *data, char **env)
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
	data->env_var = new_env;
}
