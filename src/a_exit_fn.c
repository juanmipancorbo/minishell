/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exit_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:22:09 by apaterno          #+#    #+#             */
/*   Updated: 2024/09/20 16:22:09 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool isbinary(char *path, char **env)
{
	int		fd;
	char	buffer[VALUE_BUFFER];
	int		i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		path = find_exe(env, path);
	}
	read(fd, buffer, VALUE_BUFFER);
	i = 0;
	while (i < VALUE_BUFFER)
	{
		if (!ft_isprint(buffer[i]) && !ft_isspace(buffer[i]))
			return (close(fd), TRUE);
		i++;
	}
	return (FALSE);

}

void	delete_herdocf(char *heredocf)
{
	unlink(heredocf);
	free(heredocf);
}

void check_arguments(char **argv, char **env)
{
	if (access(argv[1], F_OK))
	{
		file_error(ft_strjoin("-Minishell: ", argv[1]), 127);
		exit(127);
	}
	if (is_directory(argv[1]))
		cmd_error(ft_strjoin(argv[1], ": Is a directory\n"), 126);
	else
		if (isbinary(argv[1],env))
			printf("BINARIO");
		else
			printf("ARCHIVO");
	exit (0);
}