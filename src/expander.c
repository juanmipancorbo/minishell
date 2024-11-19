/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/19 20:26:53 by jpancorb         ###   ########.fr       */
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

static void	expand_token_value(t_token *token, t_utils *utils)
{
	char	*expanded;

	if (token->type == WORD && ft_strchr(token->value, '$'))
	{
		token->type = VAR;
		expanded = expand_dollars((const char *)token->value, utils);
		free(token->value);
		token->value = expanded;
	}
}

static void	add_relative_prefix(t_token *token)
{
	char	*relative;
	size_t	len;

	if (token->type == WORD && ft_strchr(token->value, '/')
		&& (token->value[0] != '/' && token->value[0] != '.'))
	{
		len = ft_strlen(token->value) + 3;
		relative = malloc(len);
		if (!relative)
			return ;
		ft_strlcpy(relative, "./", len);
		ft_strlcat(relative, token->value, len);
		free(token->value);
		token->value = relative;
	}
}

static void	to_reorder_rd(t_token **tokens)
{
	t_token	*curr;
	t_token	*rd;
	t_token	*head;

	curr = *tokens;
	if ((curr->type >= 2 && curr->type <= 5) && curr->next->next)
	{
		rd = curr;
		head = rd->next->next;
		while (curr->next)
			curr = curr->next;
		curr->next = rd;
		rd->prev = curr;
		head->prev = NULL;
		rd->next->next = NULL;
		*tokens = head;
	}
}

void	expand_tokens(t_token **tokens, t_utils *utils)
{
	t_token	*curr;

	to_reorder_rd(tokens);
	curr = *tokens;
	while (curr)
	{
		expand_token_value(curr, utils);
		add_relative_prefix(curr);
		curr = curr->next;
	}
	between_q(tokens);
}

// void	expand_tokens(t_token *tokens, t_utils *utils)
// {
// 	t_token	*curr;
// 	char	*expanded;
// 	char	*relative;
// 	size_t	len;

// 	curr = tokens;
// 	while (curr)
// 	{
// 		if (curr->type == WORD && ft_strchr(curr->value, '$'))
// 		{
// 			curr->type = VAR;
// 			expanded = expand_dollars((const char *)curr->value, utils);
// 			free(curr->value);
// 			curr->value = expanded;
// 		}
// 		// corrercion agustin
// 		if (tokens->type == WORD && ft_strchr(tokens->value, '/')
// 			&& (tokens->value[0] != '/' && tokens->value[0] != '.'))
// 		{
// 			len = ft_strlen(tokens->value) + 3;
// 			relative = malloc(len);
// 			ft_strlcpy(relative, "./", len);
// 			ft_strlcat(relative, tokens->value, len);
// 			free(curr->value);
// 			curr->value = relative;
// 		}
// 		curr = curr->next;
// 	}
// 	between_q(&tokens);
// }


