/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:08:48 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/25 17:59:25 by jpancorb         ###   ########.fr       */
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

static void	handle_arguments(t_token *token, t_cmd *cmd)
{
	if (token->type == VAR || token->type == QUOTED)
	{
		if (cmd->args && ft_strncmp(cmd->args[0], "echo", 5) == 0
			&& token->value && ft_strlen(token->value) > 0)
			add_arg(cmd, ft_strdup(token->value));
		else if (token->value && ft_strlen(token->value) > 0)
			expand_and_add_arg(cmd, token->value);
	}
	else if (token->type == WORD || token->type == SINGLE_Q)
		add_arg(cmd, ft_strdup(token->value));
}

t_bool	parse_tkn(t_token *token, t_cmd *cmd)
{
	if (token->type == VAR || token->type == QUOTED || token->type == WORD
		|| token->type == SINGLE_Q)
		handle_arguments(token, cmd);
	else if (token->type >= 2 && token->type <= 5)
		handle_redirections(token, cmd);
	return (TRUE);
}
