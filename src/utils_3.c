/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:55:43 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/22 18:57:54 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_export_name(char *var_name, t_utils *utils)
{
	int		i;
	char	**env;
	size_t	var_len;

	i = 0;
	env = utils->export_var;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, var_len))
			return (0);
		i++;
	}
	return (-1);
}
