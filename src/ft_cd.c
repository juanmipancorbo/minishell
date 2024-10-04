/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:02:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/04 17:02:02 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <limits.h>

int	ft_cd(t_cmd *cmd, t_utils *utils)
{
	char	*path;
	char	*home;
	char	cwd[1024];

	if (!cmd->args[1])
	{
		home = expand_var("HOME", utils->env_var);
		chdir(home);
		free(home);
	}
	else
	{
		path = cmd->args[1];
		chdir(path);
	}
	if (getcwd(cwd, sizeof(cwd)))
		replace_env_var("PWD", cwd, utils);
	return (0);
}
