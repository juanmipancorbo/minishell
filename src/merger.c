/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:30 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/21 20:19:59 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	to_check_merge(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr && curr->value)
	{
		if (curr->type == QUOTED || curr->type == SINGLE_Q)
			return (0);
		if (curr->type == PIPE)
			return (1);
		curr++;
	}
	return (1);
}

static int	calculate_merge_length(t_token *curr)
{
	int	len;

	len = 0;
	while (curr && (curr->type == WORD || curr->type == QUOTED
			|| curr->type == SINGLE_Q))
	{
		len += ft_strlen(curr->value);
		curr = curr->next;
	}
	return (len);
}

static char	*merge_values(t_token *curr, int len)
{
	char	*merged;
	char	*temp;

	merged = (char *)malloc(sizeof(char) * (len + 1));
	if (!merged)
		return (NULL);
	merged[0] = '\0';
	while (curr && (curr->type == WORD || curr->type == QUOTED
			|| curr->type == SINGLE_Q))
	{
		if (curr->type == SINGLE_Q)
			curr->type = QUOTED;
		temp = ft_strjoin(merged, curr->value);
		free(merged);
		free(curr->value);
		merged = temp;
		curr = curr->next;
	}
	return (merged);
}

static void	free_merged_tokens(t_token *curr)
{
	t_token	*to_free;

	while (curr && (curr->type == WORD || curr->type == QUOTED
			|| curr->type == SINGLE_Q))
	{
		to_free = curr;
		curr = curr->next;
		free(to_free);
	}
}

void	to_merge_words(t_token *token)
{
	char		*merged;
	t_token		*curr;
	t_token		*to_free;
	int			len;

	curr = token->next;
	if (!curr->next || to_check_merge(curr))
		return ;
	len = calculate_merge_length(curr);
	merged = merge_values(curr, len);
	if (!merged)
		return ;
	to_free = token->next->next;
	token->next->value = merged;
	while (curr && (curr->type == WORD || curr->type == QUOTED
			|| curr->type == SINGLE_Q))
		curr = curr->next;
	token->next->next = curr;
	free_merged_tokens(to_free);
}
