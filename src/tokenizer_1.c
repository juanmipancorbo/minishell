/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 11:54:00 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	to_empty_string(t_token **head, t_token **curr, const char ***input)
{
	t_token		*token;

	(**input)--;
	if (***input == '\'' || ***input == '"')
	{
		if (***input == *((**input) + 1))
		{
			token = new_token(WORD, "");
			add_token_node(head, curr, &token);
		}
		(**input) += 2;
	}
	else
		(**input) += 2;
}

static void	to_quotes(const char **input, t_token **head, t_token **curr)
{
	t_token		*token;
	char		q_type;
	char		*content;

	q_type = (char)**input;
	(*input)++;
	if (q_type == '"' && **input != q_type)
		double_q(input, head, curr);
	else if (**input != q_type)
	{
		content = single_q(input, q_type);
		token = new_token(SINGLE_Q, content);
		free(content);
		add_token_node(head, curr, &token);
	}
	if (**input == q_type)
		to_empty_string(head, curr, &input);
}

static void	to_redirect(const char **input, t_token **head, t_token **curr)
{
	char		op;
	t_token		*token;

	op = **input;
	(*input)++;
	if (**input == op)
	{
		(*input)++;
		if (op == '<')
			token = new_token(HEREDOC, "<<");
		else
			token = new_token(APPEND, ">>");
	}
	else
	{
		if (op == '<')
			token = new_token(RD_IN, "<");
		else
			token = new_token(RD_OUT, ">");
	}
	add_token_node(head, curr, &token);
}

static void	to_pipe(const char **input, t_token **head, t_token **curr)
{
	t_token	*token;

	(*input)++;
	token = new_token(PIPE, "|");
	add_token_node(head, curr, &token);
}

t_token	*to_tokenize(const char *input)
{
	t_token		*head;
	t_token		*curr;

	if (!input)
		return (NULL);
	head = NULL;
	curr = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '\'' || *input == '"')
			to_quotes(&input, &head, &curr);
		else if (*input == '<' || *input == '>')
			to_redirect(&input, &head, &curr);
		else if (*input == '|')
			to_pipe(&input, &head, &curr);
		else if (*input)
			to_word(&input, &head, &curr);
	}
	return (head);
}
