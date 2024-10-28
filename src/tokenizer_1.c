/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/28 21:52:20 by jpancorb         ###   ########.fr       */
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
		manage_error("Error: Unmatched quotes.\n");
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

static void	analyze_symbol(const char **input)
{
	if (**input == '=')
	{
		(*input)++;
		if (**input == '\'' || **input == '"')
		{
			(*input)++;
			if (ft_strchr(*input, '\'') || ft_strchr(*input, '"'))
			{
				while (**input && **input != '\'' && **input != '"')
					(*input)++;
				if (**input)
					(*input)++;
			}
		}
	}
	else
		(*input)++;
}

static void	to_word(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	start = *input;
	while (**input && !ft_isspace(**input) && **input != '|' && **input != '<'
		&& **input != '>' && **input != '\'' && **input != '"')
		analyze_symbol(input);
	len = *input - start;
	value = ft_strndup(start, len);
	if (!value)
		manage_error("Malloc error (to_word).");
	token = new_token(WORD, value);
	free(value);
	add_token_node(head, curr, &token);
}

// static void	to_word(const char **input, t_token **head, t_token **curr)
// {
// 	const char	*start;
// 	char		*value;
// 	t_token		*token;
// 	size_t		len;

// 	start = *input;
// 	while (**input && !ft_isspace(**input) && **input != '|' && **input != '<'
// 		&& **input != '>' && **input != '\'' && **input != '"')
// 	{
// 		if (**input == '=')
// 		{
// 			(*input)++;
// 			if (**input == '\'' || **input == '"')
// 			{
// 				(*input)++;
// 				if (ft_strchr(*input, '\'') || ft_strchr(*input, '"'))
// 				{
// 					while (**input && **input != '\'' && **input != '"')
// 						(*input)++;
// 					(*input)++;
// 				}
// 			}
// 		}
// 		else
// 			(*input)++;
// 	}
// 	len = *input - start;
// 	value = ft_strndup(start, len);
// 	if (!value)
// 		manage_error("Malloc error(to_word)).");
// 	token = new_token(WORD, value);
// 	free(value);
// 	add_token_node(head, curr, &token);
// }

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
		else
			to_word(&input, &head, &curr);
	}
	return (head);
}
