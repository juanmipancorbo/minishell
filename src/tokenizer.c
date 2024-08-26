/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:08 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/26 22:26:07 by jpancorb         ###   ########.fr       */
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

t_token	*to_redirect(const char **input)
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
	return (token);
}

t_token	*to_word(const char **input)
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
		exit(1);
	}
	ft_strlcpy(start, len);
	token = new_token(WORD, value);
	free(value);
	return (token);
}

t_token	*to_tokenize(const char *input)
{
	t_token		*head;
	t_token		*curr;
	t_token		*token;

	head = NULL;
	curr = NULL;
	while (*input)
	{
		if (ft_isspace(&input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '<' || *input == '>')
			token = to_redirect(&input);
		else if (*input == '|')
			token = new_token(PIPE, "|");
		else
			token = to_word(&input);
	}
	if (!head)
		head = token;
	else
		curr->next = token;
	curr = token;
}
