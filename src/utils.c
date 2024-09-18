/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:26:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/18 19:35:06 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(n + 1);
	if (!copy)
		return (NULL);
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst);
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

void	free_env_copy(char **env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return ;
	while (env_var[i])
	{
		free(env_var[i]);
		i++;
	}
	free(env_var);
}
