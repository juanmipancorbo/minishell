/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/13 16:47:07 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		(*input)++;
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

static void	to_word(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	start = *input;
	if ((*head) && !ft_strncmp((*head)->value, "echo", 4) && *start == '$')
		while (**input && **input != '|' && **input != '<'
			&& **input != '>' && **input != '\'' && **input != '"')
			(*input)++;
	else
		while (**input && **input != '"' && **input != '|' && **input != '<'
			&& **input != '>' && **input != '\'' && !ft_isspace(**input))
			analyze_symbol(input);
	len = *input - start;
	value = ft_strndup(start, len);
	if (!value)
		exit_error(MALLOC_E, 10);
	token = new_token(WORD, value);
	free(value);
	add_token_node(head, curr, &token);
}

t_token	*to_tokenize(const char *input)
{
	t_token		*head;
	t_token		*curr;

	head = NULL;
	curr = NULL;
	if (*input == '|' && (!*input + 1))
		printf("minishell: syntax error near unexpected token `|'\n");
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
