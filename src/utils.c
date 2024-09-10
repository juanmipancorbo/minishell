/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:26:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/10 22:15:24 by jpancorb         ###   ########.fr       */
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

	copy = (char *)malloc(n + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, n + 1);
	return (copy);
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
