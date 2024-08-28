/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/28 07:22:45 by jpancorb         ###   ########.fr       */
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
		exit(1);
	}
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token_node(t_token **head, t_token **curr, t_token **token)
{
	if ((*head) == NULL)
		*head = *token;
	else
		(*curr)->next = *token;
	*curr = *token;
}

char	*to_q_content(const char **input, char q_type)
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
		exit(1);
	}
	ft_strlcpy(content, start, len);
	return (content);
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
		exit(1);
	}
	ft_strlcpy(value, start, len);
	token = new_token(VAR, value);
	free(value);
	add_token_node(head, curr, &token);
}
