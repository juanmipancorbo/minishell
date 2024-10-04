/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:27:07 by apaterno          #+#    #+#             */
/*   Updated: 2024/10/04 18:59:45 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void sig_handler(int sig)
{
	(void)sig;
	write(1,"\n",1);
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
