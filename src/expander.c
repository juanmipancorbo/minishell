/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/17 18:27:57 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_var(char *var, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len) && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	expand_tokens(t_token *tokens, char **env)
{
	t_token	*curr;
	char	*expanded;

	curr = tokens;
	while (curr)
	{
		if (curr->type == VAR)
		{
			expanded = expand_var(curr->value, env);
			free(curr->value);
			curr->value = expanded;
		}
		curr = curr->next;
	}
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

static void	free_q(t_token **curr, t_token **end)
{
	*end = *curr;
	*curr = (*curr)->next;
	free((*end)->value);
	free(*end);
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
			start->type = WORD;
			start->next = curr;
		}
		else
			curr = curr->next;
	}
}
