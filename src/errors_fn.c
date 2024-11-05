/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:38:33 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/03 17:38:33 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	manage_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	file_error(char *msg, int exit_code)
{
	perror(msg);
	g_exit_code = exit_code;
	free(msg);
}

void	cmd_error(char *str, int exit_code)
{
	ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	exit(exit_code);
}

void	heredoc_error(char *delimiter)
{
	char	*msg;

	msg = ft_strjoin("Minishell: warning: here-document\
 delimited by end-of-file, wanted:", delimiter);
	ft_putendl_fd(msg, STDIN_FILENO);
	free(msg);
}
