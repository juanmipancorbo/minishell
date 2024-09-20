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

bool	check_files(char *path)
{
	return (access(path, F_OK));
}

static void	delete_herdocf(void)
{
	if (check_files(HERDOC_F) == 0)
		unlink(HERDOC_F);
}

void	clean_exit(t_cmd *cmd)
{
	delete_herdocf();
	(void)cmd;
}
