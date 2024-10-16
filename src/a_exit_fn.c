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

t_bool	check_files(char *path)
{
	return (access(path, F_OK));
}

void	delete_herdocf(void)
{
	if (check_files(HEREDOC_F) == 0)
		unlink(HEREDOC_F);
}

void exit_status(int status)
{
	if (WIFEXITED(status))
		printf("%d", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("130");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("131");
	}
	else if (WIFSTOPPED(status))
		printf("%d",WSTOPSIG(status));
	else
		printf("%d",WTERMSIG(status));
}
