/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:27:07 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/05 12:59:39 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		write(1, "\n", 1);
		exit(130);
	}
}

static void	heredoc_wait(int sig)
{
	if (sig == SIGINT)
		g_exit_code = 130;
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
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
		g_exit_code = 131;
		write(STDOUT_FILENO, "Quit\n", 5);
	}
}

void	init_signals(int i)
{
	if (i == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 0)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
	else if (i == 2)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 3)
	{
		signal(SIGINT, heredoc_wait);
		signal(SIGQUIT, SIG_IGN);
	}
}
