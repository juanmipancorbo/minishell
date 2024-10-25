/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:27:07 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/25 13:35:08 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_process(t_utils *utils, int nb_process)
{
	int	i;
	int status;

	i = 0;
	while (i < nb_process)
	{
		waitpid(utils->process_id[i], &status, 0);
		printf("PID:%d\n",utils->process_id[i]);
		i++;
	}
	if (WIFEXITED(status))
		printf("-%d\n", WEXITSTATUS(status));
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		rl_on_new_line();
	}
}

void	init_signals(int i)
{
	if (i)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
}
