/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:27:36 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/25 08:43:22 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	skip_special_chars(const char **input)
{
	if (**input && **input == '$' && ((*input)[1] == '"'
		|| (*input)[1] == '\''))
	{
		(*input)++;
		return (TRUE);
	}
	return (FALSE);
}

void	to_word(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	start = *input;
	if (skip_special_chars(input))
		return ;
	if ((*head) && !ft_strncmp((*head)->value, "echo", 4)
		&& (*curr)->type != PIPE && (**input != '-' && (**input + 1) != 'n'))
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
	add_token_node(head, curr, &token, input);
}

char	*concat_q(t_token *token)
{
	char	*result;
	char	*temp;
	t_token	*curr;

	result = ft_strdup("");
	curr = token;
	while (curr && curr->type != DOUBLE_Q)
	{
		if (curr->type == WORD || curr->type == VAR)
		{
			temp = result;
			result = ft_strjoin(result, curr->value);
			free(temp);
		}
		curr = curr->next;
	}
	return (result);
}

void	between_q(t_token **tokens)
{
	t_token	*curr;
	t_token	*start;
	t_token	*end;
	char	*concat;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == DOUBLE_Q)
		{
			start = curr;
			curr = curr->next;
			concat = concat_q(curr);
			while (curr && curr->type != DOUBLE_Q)
				free_q(&curr, &end);
			free_q(&curr, &end);
			free(start->value);
			start->value = concat;
			start->type = QUOTED;
			start->next = curr;
		}
		else if (curr->type == VAR && ft_strchr(curr->value, '"'))
			to_remove_quotes(&curr->value);
		curr = curr->next;
	}
}

void	insert_new_tokens(t_token *curr, char **split_words)
{
	t_token	*token;
	int		i;

	i = 0;
	while (split_words[i])
	{
		if (i == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(split_words[i]);
		}
		else
		{
			token = new_token(WORD, ft_strdup(split_words[i]));
			token->next = curr->next;
			curr->next = token;
			curr = token;
		}
		i++;
	}
}
