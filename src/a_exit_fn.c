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

void	delete_herdocf(char *heredocf)
{
	unlink(heredocf);
	free(heredocf);
}

void	error_msg(char *msg, int exit_code)
{
	printf("%s\n", msg);
	g_exit_code = exit_code;
}

t_bool sintax_error(const char *input)
{
	if (*input == '|' && *(input + 1) == '|')
	{
		error_msg("minishell: syntax error near unexpected token '||'", 2);
		return (TRUE);
	}
	if (*input == '|' && *(input + 1) == '\0')
	{
		error_msg("minishell: syntax error near unexpected token '|'", 2);
		return (TRUE);
	}
	return (FALSE);
}