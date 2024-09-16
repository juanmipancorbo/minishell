/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:49 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/16 21:30:36 by jpancorb         ###   ########.fr       */
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