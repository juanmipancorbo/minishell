/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/27 17:06:58 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(t_tkn_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		manage_error("Malloc error(new_token).");
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
	add_token_node(head, curr, &token);
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
		manage_error("Malloc error(single_q).");
	return (content);
}

void	double_q(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	t_token		*token;

	start = *input;
	token = new_token(DOUBLE_Q, "\"");
	add_token_node(head, curr, &token);
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			if (*input > start)
				q_content(start, *input, head, curr);
			to_variable(input, head, curr);
			start = *input;
		}
		else
			(*input)++;
	}
	if (*input > start)
	{
		q_content(start, *input, head, curr);
		token = new_token(DOUBLE_Q, "\"");
		add_token_node(head, curr, &token);
	}
}

void	to_variable(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	(*input)++;
	if (**input && (!ft_isalnum(**input) || **input != '_'))
		return ;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	len = *input - start;
	value = ft_strndup(start, len);
	if (!value)
		manage_error("Malloc error(to_variable).");
	token = new_token(VAR, value);
	free(value);
	add_token_node(head, curr, &token);
}
