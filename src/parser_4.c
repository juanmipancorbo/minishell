/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:08:48 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/22 13:22:07 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redirections(t_token *token, t_cmd *cmd)
{
	if (token->type >= RD_IN && token->type <= HEREDOC)
		to_merge_words(token);
	token = token->next;
	add_red(cmd, token->value, token->prev->type);
	if (token->type == QUOTED)
	{
		if (cmd->in_rd)
			cmd->in_rd->quoted = 1;
		if (cmd->out_rd)
			cmd->out_rd->quoted = 1;
	}
}

static t_bool	validate_syntax(t_token *token)
{
	if (!token->next || (token->next->type != WORD
			&& token->next->type != QUOTED
			&& token->next->type != SINGLE_Q && token->next->type != RD_OUT))
	{
		// parche agustin
		// printf("Minishell: syntax error near unexpected token `%s'\n",
		// 	token->next->value);
		printf("Minishell: syntax error near unexpected token \n");
		g_exit_code = 2;
		return (FALSE);
	}
	return (TRUE);
}

static void	handle_arguments(t_token *token, t_cmd *cmd)
{
	if (token->type == VAR || token->type == QUOTED)
	{
		if (cmd->args && ft_strncmp(cmd->args[0], "echo", 5) == 0)
			add_arg(cmd, ft_strdup(token->value));
		else
			expand_and_add_arg(cmd, token->value);
	}
	else if (token->type == WORD || token->type == SINGLE_Q)
		add_arg(cmd, ft_strdup(token->value));
}

t_bool	parse_tkn(t_token *token, t_cmd *cmd)
{
	if (token->type == UNMATCHED)
		cmd->args = NULL;
	else if (token->type == VAR || token->type == QUOTED || token->type == WORD
		|| token->type == SINGLE_Q)
		handle_arguments(token, cmd);
	else if (token->type >= 2 && token->type <= 5)
	{
		if (!validate_syntax(token))
			return (FALSE);
		handle_redirections(token, cmd);
	}
	return (TRUE);
}
