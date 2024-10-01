/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/19 21:12:42 by jpancorb         ###   ########.fr       */
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

void	insert_new_tokens(t_token *curr, char **split_words)
{
	t_token	*token;
	t_token	*prev;
	int		i;

	//error make //
	prev = curr;
	(void)prev;
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

void	expand_tokens(t_token *tokens, char **env)
{
	t_token	*curr;
	char	*expanded;
	char	**split_words;

	curr = tokens;
	while (curr)
	{
		if (curr->type == VAR)
		{
			expanded = expand_var(curr->value, env);
			split_words = ft_split(expanded, ' ');
			free(expanded);
			insert_new_tokens(curr, split_words);
			ft_free_split(split_words);
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
