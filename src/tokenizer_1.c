/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/10 22:24:10 by jpancorb         ###   ########.fr       */
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
		if (q_type == '"')
			double_q(input, head, curr);
		else
		{
			content = single_q(input, q_type);
			token = new_token(WORD, content);
			free(content);
			add_token_node(head, curr, &token);
		}
	}
	else
	{
		perror("Error: Unmatched quotes.\n");
		exit(EXIT_FAILURE);
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
	while (**input && !ft_isspace(**input) && **input != '|'
		&& **input != '<' && **input != '>')
		(*input)++;
	len = *input - start + 1;
	value = malloc(len);
	if (!value)
	{
		perror("Malloc error(to_word)).");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(value, start, len);
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
		else if (*input == '$')
			to_variable(&input, &head, &curr);
		else
			to_word(&input, &head, &curr);
	}
	return (head);
}
