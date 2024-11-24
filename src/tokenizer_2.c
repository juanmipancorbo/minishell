/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 16:47:22 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(t_tkn_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit_error(MALLOC_E, 10);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	q_content(const char *start, const char *input, t_token **head,
			t_token **curr)
{
	char	*content;
	t_token	*token;

	content = ft_strndup(start, input - start);
	token = new_token(WORD, content);
	free(content);
	add_token_node(head, curr, &token, &input);
}

char	*single_q(const char **input, char q_type)
{
	const char	*start;
	char		*content;
	size_t		len;

	start = *input;
	while (**input && **input != q_type)
		(*input)++;
	len = *input - start;
	content = ft_strndup(start, len);
	if (!content)
		exit_error(MALLOC_E, 10);
	return (content);
}

void	double_q(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	t_token		*token;

	start = *input;
	token = new_token(DOUBLE_Q, "\"");
	add_token_node(head, curr, &token, input);
	while (**input && **input != '"')
		(*input)++;
	if (*input > start)
	{
		q_content(start, *input, head, curr);
		token = new_token(DOUBLE_Q, "\"");
		add_token_node(head, curr, &token, input);
	}
}

void	to_variable(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	(*input)++;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	len = *input - start + 1;
	value = ft_strndup(--start, len);
	if (!value)
		exit_error(MALLOC_E, 10);
	token = new_token(WORD, value);
	free(value);
	add_token_node(head, curr, &token, input);
}
