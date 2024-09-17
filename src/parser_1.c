/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:13:32 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/17 18:11:03 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_in_red(t_cmd *cmd, t_red *red)
{
	t_red	*temp;

	if (!cmd->in_rd)
		cmd->in_rd = red;
	else
	{
		temp = cmd->in_rd;
		while (temp->next)
			temp = temp->next;
		temp->next = red;
	}
}

static void	add_out_red(t_cmd *cmd, t_red *red)
{
	t_red	*temp;

	if (!cmd->out_rd)
		cmd->out_rd = red;
	else
	{
		temp = cmd->out_rd;
		while (temp->next)
			temp = temp->next;
		temp->next = red;
	}
}

static void	add_red(t_cmd *cmd, char *file, int type)
{
	t_red	*red;

	red = create_red_node(file, type);
	if (!red)
		return ;
	if (type == RD_IN || type == HEREDOC)
		add_in_red(cmd, red);
	else if (type == RD_OUT || type == APPEND)
		add_out_red(cmd, red);
}

static void	parse_tkn(t_token *token, t_cmd *cmd)
{
	if (token->type == WORD || token->type == VAR)
		add_arg(cmd, token->value);
	else if (token->type == RD_IN || token->type == RD_OUT
		|| token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next || token->next->type != WORD)
		{
			printf("Error: A file was expected.\n");
			return ;
		}
		token = token->next;
		add_red(cmd, token->value, token->prev->type);
		return ;
	}
}

t_cmd	*to_parse(t_token *tokens, char **env)
{
	t_cmd	*head;
	t_cmd	*curr;

	expand_tokens(tokens, env);
	between_q(&tokens);
	head = create_cmd_node();
	if (!head)
		return (NULL);
	curr = head;
	while (tokens)
	{
		if (tokens->type == PIPE)
			curr = add_pipe(curr);
		else
		{
			parse_tkn(tokens, curr);
			if (tokens->type == RD_IN || tokens->type == RD_OUT
				|| tokens->type == APPEND || tokens->type == HEREDOC)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
