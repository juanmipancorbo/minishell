/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:42:44 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/01 17:42:44 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_flag(char *arg, int *i, int *newline)
{
	int	j;

	j = 2;
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[j])
		{
			if (arg[j] != 'n' )
				return ;
			j++;
		}
		*newline = 0;
		*i = 2;
	}
}

static t_bool	print_args(char *arg)
{
	int	i;

	i = 2;
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (TRUE);
			i++;
		}
	}
	else
		return (TRUE);
	return (FALSE);
}

int	ft_echo(t_cmd *cmd, t_utils *utils)
{
	int	i;
	int	checker;
	int	newline;

	(void)utils;
	i = 1;
	newline = 1;
	checker = 0;
	check_flag(cmd->args[1], &i, &newline);
	while (cmd->args[i])
	{
		if (print_args(cmd->args[i]))
			checker = 1;
		if (checker)
		{
			write(1, cmd->args[i], ft_strlen(cmd->args[i]));
			// if (cmd->args[i + 1] != NULL)
				// write(1, " ", 1);
		}
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
