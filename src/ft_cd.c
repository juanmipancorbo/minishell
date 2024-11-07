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
		getcwd(cwd, sizeof(cwd));
		path = cmd->args[1];
		if (!check_env_name("OLDPWD", utils, 2))
			replace_env_var("OLDPWD", cwd, utils->export_var);
		if (check_env_name("OLDPWD", utils, 1))
			add_env_var("OLDPWD", cwd, &utils->env_var);
		chdir(path);
		getcwd(cwd, sizeof(cwd));
		replace_env_var("PWD", cwd, utils->env_var);
		replace_env_var("PWD", cwd, utils->export_var);
	}
	return (0);
}
