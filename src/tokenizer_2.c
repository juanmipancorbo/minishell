/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/03 21:44:34 by jpancorb         ###   ########.fr       */
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
	token->prev = NULL;
	return (token);
}

void	add_token_node(t_token **head, t_token **curr, t_token **token)
{
	if (*head == NULL)
		*head = *token;
	else
	{
		(*curr)->next = *token;
		(*token)->prev = *curr;
	}
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
	char		*expand_value;
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
	expand_value = getenv(value);
	if (!expand_value)
		expand_value = "";
	token = new_token(VAR, expand_value);
	free(value);
	add_token_node(head, curr, &token);
}

char	*to_expand(const char *str)
{
	char		*result;
	char		*temp;
	char		*var_name;
	char		*value;
	const char	*start;

	result = ft_strdup("");
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			start = str;
			while (ft_isalnum(*str) || *str == '_')
				str++;
			var_name = ft_substr(start, 0, str - start);
			value = getenv(var_name);
			if (!value)
				value = "";
			temp = ft_strjoin(result, value);
			free(result);
			result = temp;
			free(var_name);
		}
		else
		{
			temp = malloc(2);
			if (!temp)
			{
				perror("Malloc error(to_expand).");
				exit(EXIT_FAILURE);
			}
			temp[0] = *str;
			temp[1] = '\0';
			result = ft_strjoin(result, temp);
			str++;
		}
	}
	return (result);
}
