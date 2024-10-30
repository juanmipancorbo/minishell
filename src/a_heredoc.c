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

void	read_loop(char *str)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (fd < 0)
		manage_error(ERROR);
	init_signals(2);
	while (1)
	{
		line = readline(">");
		//init_signals(0);
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
}
