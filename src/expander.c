/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/14 18:15:16 by jpancorb         ###   ########.fr       */
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

void	expand_tokens(t_token *tokens, t_utils *utils)
{
	t_token	*curr;
	char	*expanded;
	char	*relative;
	size_t	len;

	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD && ft_strchr(curr->value, '$'))
		{
			curr->type = VAR;
			expanded = expand_dollars((const char *)curr->value, utils);
			free(curr->value);
			curr->value = expanded;
		}
		if (tokens->type == WORD && ft_strchr(tokens->value, '/')
			&& tokens->value[0] != '/')
		{
			len = ft_strlen(tokens->value) + 3;
			relative = malloc(len);
			ft_strlcpy(relative, "./", len);
			ft_strlcat(relative, tokens->value, len);
			free(curr->value);
			curr->value = relative;
		}
		curr = curr->next;
	}
	between_q(&tokens);
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
		else
			curr = curr->next;
	}
}
