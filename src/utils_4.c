/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:18:47 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:47 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	analyze_symbol(const char **input)
{
	if (**input == '=')
	{
		(*input)++;
		if (**input == '\'' || **input == '"')
		{
			(*input)++;
			if (ft_strchr(*input, '\'') || ft_strchr(*input, '"'))
			{
				while (**input && **input != '\'' && **input != '"')
					(*input)++;
				if (**input)
					(*input)++;
			}
		}
	}
	else
		(*input)++;
}

void	to_get_pid(t_utils *utils)
{
	int		fd;
	int		bytes_read;
	char	buffer[256];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return ;
	bytes_read = read(fd, buffer, 255);
	if (bytes_read == -1)
	{
		close(fd);
		return ;
	}
	buffer[bytes_read] = '\0';
	parse_pid(utils, buffer);
	close(fd);
}

int	cmd_lst_size(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	if (cmd == NULL)
		return (0);
	tmp = *cmd;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

pid_t	*get_pid_array(int nbs_process)
{
	pid_t	*pid_arr;

	pid_arr = malloc(sizeof(pid_t) * nbs_process);
	if (!pid_arr)
		exit_error(MALLOC_E, 10);
	return (pid_arr);
}

void	check_arg(char **argv)
{
	if (!ft_strncmp(argv[0], argv[1], ft_strlen(argv[0]) + 1))
	{
		ft_printf_fd("minishell: %s: %s\n", argv[1],
			"cannot execute binary file");
		exit (126);
	}
	else
	{
		ft_printf_fd("minishell: %s: %s\n", argv[1],
			"No such file or directory");
		exit (127);
	}
}
