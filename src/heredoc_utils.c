/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:06 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/13 13:13:14 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	expand_split(char **split, t_utils *utils)
{
	int		i;
	char	*expanded;

	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '$'))
		{
			expanded = expand_dollars((const char *)split[i], utils);
			free(split[i]);
			split[i] = expanded;
		}
		i++;
	}
}

void	expand_hd_word(char *line, t_utils *utils, int fd)
{
	int		i;
	int		j;
	char	**split_hd;

	i = 0;
	j = 0;
	split_hd = ft_split(line, 32);
	expand_split(split_hd, utils);
	while (line[j])
	{
		while (line[j] != 32 && line[j])
			j++;
		ft_putstr_fd(split_hd[i++], fd);
		while (line[j] && line[j] == 32)
			write(fd, &line[j++], 1);
	}
	write(fd, "\n", 1);
	clean_split(split_hd);
}
// int  *heredoc_quotes(char *delimiter)
// {
// 	char *newdelimiter;
// 	int i;
	
	
	
// }

