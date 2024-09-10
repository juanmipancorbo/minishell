/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/10 22:19:52 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(t_tkn_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Malloc error(new_token).");
		exit(EXIT_FAILURE);
	}
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

	len = 0;
	start = *input;
	while (**input && **input != q_type)
		(*input)++;
	len = *input - start + 1;
	content = malloc(len);
	if (!content)
	{
		perror("Malloc error(to_quotes).");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(content, start, len);
	return (content);
}

void	double_q(const char **input, t_token **head, t_token **curr)
{
	const char	*start;

	start = *input;
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
		q_content(start, *input, head, curr);
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
	value = malloc(len);
	if (!value)
	{
		perror("Malloc error(to_variable).");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(value, start, len);
	token = new_token(VAR, value);
	free(value);
	add_token_node(head, curr, &token);
}
