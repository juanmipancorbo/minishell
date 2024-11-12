/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:26:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/11 22:13:36 by jpancorb         ###   ########.fr       */
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
	if ((*token)->type == UNMATCHED)
	{
		(*token)->next = *head;
		(*curr)->next = NULL;
		(*head)->prev = *token;
		*head = *token;
	}
	else if (*head == NULL)
		*head = *token;
	else
	{
		(*curr)->next = *token;
		(*token)->prev = *curr;
	}
	*curr = *token;
}

void	free_env_copy(t_utils *utils)
{
	int	i;

	i = 0;
	if (utils->env_var)
	{
		while (utils->env_var[i])
			free(utils->env_var[i++]);
		free(utils->env_var);
		utils->env_var = NULL;
	}
	i = 0;
	if (utils->export_var)
	{
		while (utils->export_var[i])
			free(utils->export_var[i++]);
		free(utils->export_var);
		utils->export_var = NULL;
	}
	if (utils->pid)
		free(utils->pid);
	if (utils->process_id)
		free(utils->process_id);
}
