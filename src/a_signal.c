/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:27:07 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/29 15:42:56 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_process(t_utils *utils, int nb_process)
{
	int status;
	int i;

	i = 0;
	while (i < nb_process)
	{
		waitpid(utils->process_id[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exit_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_exit_code = 131;
	}
	init_signals(1);
	// 	else if (WIFSTOPPED(status))
	// 	printf("%d\n",WSTOPSIG(status));
	// else
	// 	printf("+%d\n",WTERMSIG(status));
		
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
		g_exit_code = 130;
	}
	if (sig == SIGQUIT)
	{
		g_exit_code = 130
		write(STDOUT_FILENO, "Quit\n", 5);
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
