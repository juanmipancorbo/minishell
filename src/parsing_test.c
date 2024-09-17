/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:22:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/17 18:31:48 by jpancorb         ###   ########.fr       */
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
	t_red 	*out_rd;

	while (cmds)
	{
		printf("Command:\n");
		if (cmds->args)
		{
			i = 0;
			printf("  Args:\n");
			while (cmds->args[i])
			{
				printf("    [%d]: >%s<\n", i, cmds->args[i]);
				i++;
			}
		}
		if (cmds->in_rd)
		{
			printf("  Input Redirections:\n");
			in_rd = cmds->in_rd;
			while (in_rd)
			{
				printf("    Type: %d, File: %s\n", in_rd->type, in_rd->file);
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
				out_rd = out_rd->next;
			}
		}
		cmds = cmds->next;
		printf("\n");
	}
}

void	free_redirections(t_red *red)
{
	t_red	*temp;

	while (red)
	{
		temp = red;
		red = red->next;
		free(temp->file);
		free(temp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	int		i;

	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->full_path)
			free(temp->full_path);
		if (temp->in_rd)
			free_redirections(temp->in_rd);
		if (temp->out_rd)
			free_redirections(temp->out_rd);
		free(temp);
	}
}
