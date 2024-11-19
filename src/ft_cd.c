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

static t_bool	change_directory(char *path, t_utils *utils)
{
	char	cwd[VALUE_BUFFER];

	getcwd(cwd, sizeof(cwd));
	if (!check_env_name("OLDPWD", utils, 2))
		replace_env_var("OLDPWD", cwd, utils->export_var);
	if (check_env_name("OLDPWD", utils, 1))
		add_env_var("OLDPWD", cwd, &utils->env_var);
	if (!check_env_name("OLDPWD", utils, 1))
		replace_env_var("OLDPWD", cwd, utils->env_var);
	if (chdir(path))
	{	
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (FALSE);
	}	
	getcwd(cwd, sizeof(cwd));
	replace_env_var("PWD", cwd, utils->env_var);
	replace_env_var("PWD", cwd, utils->export_var);
	return (TRUE);
}

int	ft_cd(t_cmd *cmd, t_utils *utils)
{
	char	*home;

	if (cmd->args[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!cmd->args[1])
	{
		home = expand_var("HOME", utils->env_var);
		if (home)
		{
			chdir(home);
			free(home);
		}
		else
			printf("minishell: cd: HOME not set\n");
	}
	else
		if (!change_directory(cmd->args[1], utils))
			return (1);
	return (0);
}

// int	ft_cd(t_cmd *cmd, t_utils *utils)
// {
// 	char	*path;
// 	char	*home;
// 	char	cwd[VALUE_BUFFER];

// 	if (!cmd->args[1])
// 	{
// 		home = expand_var("HOME", utils->env_var);
// 		chdir(home);
// 		free(home);
// 	}
// 	else
// 	{
// 		getcwd(cwd, sizeof(cwd));
// 		path = cmd->args[1];
// 		if (!check_env_name("OLDPWD", utils, 2))
// 			replace_env_var("OLDPWD", cwd, utils->export_var);
// 		if (check_env_name("OLDPWD", utils, 1))
// 			add_env_var("OLDPWD", cwd, &utils->env_var);
// 		if (!check_env_name("OLDPWD", utils, 1))
// 			replace_env_var("OLDPWD", cwd, utils->env_var);
// 		if (chdir(path))
// 			printf("minishell: cd: %s: No such file or directory\n", path);
// 		getcwd(cwd, sizeof(cwd));
// 		replace_env_var("PWD", cwd, utils->env_var);
// 		replace_env_var("PWD", cwd, utils->export_var);
// 	}
// 	return (0);
// }
