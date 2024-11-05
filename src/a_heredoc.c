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

static t_bool	wait_herecoc(pid_t pid)
{
	int	status;

	init_signals(3);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
		return (FALSE);
	else
		return (TRUE);
}

void	star_loop(char *delimiter, int fd)
{
	char	*line;

	init_signals(2);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	exit(0);
}

t_bool	read_loop(char *str)
{
	int		fd;
	pid_t	pid;

	fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (fd < 0)
		manage_error(ERROR);
	pid = fork();
	if (pid == 0)
		star_loop(str, fd);
	if (wait_herecoc(pid))
		return (close(fd), TRUE);
	return (close(fd), FALSE);
}

t_bool heredoc_complete(t_cmd *cmd)
{
	t_red *in;

	in = cmd->in_rd;
	if(in->type == HEREDOC)
		printf("HEREDOC\n");
	return (TRUE);
}