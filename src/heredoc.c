/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:42:56 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/23 20:49:07 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*int_to_string(int num)
{
	char	*str;
	int		i;
	int		tmp;

	str = malloc(12);
	if (!str)
		return (NULL);
	i = 0;
	if (num == 0)
		str[i++] = '0';
	else
	{
		tmp = num;
		while (tmp > 0)
		{
			tmp /= 10;
			i++;
		}
		str[i] = '\0';
		while (num > 0)
		{
			str[--i] = (num % 10) + '0';
			num /= 10;
		}
	}
	return (str);
}

char	*to_heredoc_filename(void)
{
	char	*base;
	char	*suffix;
	char	*filename;
	char	*pid_str;
	int		pid;

	base = ".heredoc_";
	suffix = ".tmp";
	pid = getpid();
	pid_str = int_to_string(pid);
	if (!pid_str)
		return (NULL);
	filename = (char *)malloc(strlen(base) + strlen(pid_str)
			+ strlen(suffix) + 1);
	if (!filename)
	{
		free(pid_str);
		return (NULL);
	}
	strcpy(filename, base);
	strcat(filename, pid_str);
	strcat(filename, suffix);
	free(pid_str);
	return (filename);
}


void	read_loop(char *str, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		manage_error("Error: Read_loop (1).");
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, str, ft_strlen(str))
			&& ft_strlen(line) == ft_strlen(str))
		{
			free(line);
			break ;
		}
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			manage_error("Error: Read_loop (2)");
		free(line);
	}
	close(fd);
}
