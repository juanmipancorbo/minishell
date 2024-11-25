/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:27 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:27 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_pwd(t_cmd *cmd, t_utils *utils)
{
	char	*pwd;
	char 	buffer[2048];

	(void)cmd;
	(void)utils;
	pwd = getcwd(buffer, sizeof(buffer));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
