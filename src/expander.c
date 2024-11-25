/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/25 17:54:21 by jpancorb         ###   ########.fr       */
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

static void	expand_token_value(t_token *token, t_utils *utils)
{
	char	*expanded;

	if (token->type == WORD && ft_strchr(token->value, '$'))
	{
		token->type = VAR;
		expanded = expand_dollars((const char *)token->value, utils);
		free(token->value);
		if (ft_strlen(expanded) > 0)
			token->value = expanded;
		else
		{
			free(expanded);
			token->value = NULL;
		}
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

void	expand_tokens(t_token **tokens, t_utils *utils)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		expand_token_value(curr, utils);
		add_relative_prefix(curr);
		curr = curr->next;
	}
	between_q(tokens);
}
