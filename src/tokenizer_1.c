/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/22 19:48:20 by apaterno         ###   ########.fr       */
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
	if (ft_strchr(*input, q_type))
	{
		if (q_type == '"' && **input != q_type)
			double_q(input, head, curr);
		else if (**input != q_type)
		{
			content = single_q(input, q_type);
			token = new_token(SINGLE_Q, content);
			free(content);
			add_token_node(head, curr, &token);
		}
	}
	else
	{
		to_quotes_unmatched(head, curr);
		return ;
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
	char	*content;

	(*input)++;
	if ((*input) && !ft_strncmp((*input), "|", 1))
	{
		printf("Error: \"||\" Operator not implemented.\n");
		content = ft_strdup("||");
		token = new_token(UNMATCHED, content);
		free(content);
		add_token_node(head, curr, &token);
		return ;
	}
	token = new_token(PIPE, "|");
	add_token_node(head, curr, &token);
}

t_token	*to_tokenize(const char *input)
{
	t_token		*head;
	t_token		*curr;

	head = NULL;
	curr = NULL;
	//if (*input == '|' && (!*input + 1))
	//	error_msg("minishell: syntax error near unexpected token '|'", 2);
	if (sintax_error(input))
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '\'' || *input == '"')
			to_quotes(&input, &head, &curr);
		if (head && head->type == UNMATCHED)
			break ;
		else if (*input == '<' || *input == '>')
			to_redirect(&input, &head, &curr);
		else if (*input == '|')
			to_pipe(&input, &head, &curr);
		else if (*input)
			to_word(&input, &head, &curr);
	}
	return (head);
}
