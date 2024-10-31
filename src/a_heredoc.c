/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_heredoc.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:22:39 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/20 16:22:39 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool wait_herecoc(pid_t pid)
{
	int status;

	init_signals(3);
	waitpid(pid,&status,0);
 	if (WEXITSTATUS(status) == 130)
		return (FALSE);
	else
		return (TRUE);
}

t_bool	read_loop(char *str)
{
	char	*line;
	int		fd;
	pid_t	pid;

	fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (fd < 0)
		manage_error(ERROR);
	pid = fork();
	if (pid == 0)
	{
		init_signals(2);
		while (1)
		{
			line = readline(">");
			if (!line)
				break;
			if (!ft_strncmp(line, str, ft_strlen(str) + 1))
				break;
			if (write(fd, line, ft_strlen(line)) == -1)
				manage_error(ERROR);
			if (write(fd, "\n", 1) == -1)
				manage_error(ERROR);
			free(line);
		}
	free(line);
	close(fd);
	exit(0);
	}
	if (wait_herecoc(pid))
		return (TRUE);
	return (FALSE);
}
