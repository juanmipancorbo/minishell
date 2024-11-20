/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:27:36 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/20 16:59:13 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		else
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
