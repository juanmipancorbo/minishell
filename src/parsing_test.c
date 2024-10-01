/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:22:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/20 19:14:02 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token Type: %d, Value: >%s<\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	print_var(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	print_cmds(t_cmd *cmds)
{
	int		i;
	t_red	*in_rd;
	t_red	*out_rd;

	while (cmds)
	{
		if (cmds->args)
		{
			printf("Command:\n");
			i = 0;
			printf("  Args:\n");
			while (cmds->args[i])
			{
				printf("    [%d]: >%s<\n", i, cmds->args[i]);
				i++;
			}
		}
		if (cmds->full_path)
		{
			printf("  Full path: %s\n", cmds->full_path);
		}
		if (cmds->in_rd)
		{
			printf("  Input Redirections:\n");
			in_rd = cmds->in_rd;
			while (in_rd)
			{
				printf("    Type: %d, File: %s\n", in_rd->type, in_rd->file);
				if (in_rd->fd)
					printf("    Fd: %d\n", in_rd->fd);
				in_rd = in_rd->next;
			}
		}
		if (cmds->out_rd)
		{
			printf("  Output Redirections:\n");
			out_rd = cmds->out_rd;
			while (out_rd)
			{
				printf("    Type: %d, File: %s\n", out_rd->type, out_rd->file);
				if (out_rd->fd)
					printf("    Fd: %d\n", out_rd->fd);
				out_rd = out_rd->next;
			}
		}
		printf("bi:%p\n", cmds->built_in);
		cmds = cmds->next;
	}
}
