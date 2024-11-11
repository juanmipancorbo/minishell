/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:06 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/11 13:13:16 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_hd_word(char *line, t_utils *utils, int fd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expanded = expand_dollars((const char *)line[i], utils);
			ft_putstr_fd(expanded, fd);
			free(expanded);
			while(line[i] != 32)
				i++;
		}
		write(fd, &line[i], 1);
		i++;
	}
	//between_q(&tokens);
}

void write_hd_exp(char **expansion, int fd)
{
	int i;

	i = 0;
	while(expansion[i])
	{
		ft_putstr_fd(expansion[i], fd);
		if (expansion[i + 1 != '\0'])
	}
}