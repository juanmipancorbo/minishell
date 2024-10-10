/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:00:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/10 22:05:21 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	calculate_expanded_length(const char *str, const char *pid)
{
	int	i;
	int	len;
	int	pid_len;

	i = 0;
	len = 0;
	pid_len = ft_strlen(pid);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			len += pid_len;
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expand_dollars(const char *str, const char *pid)
{
	char	*expanded;
	int		i;
	int		j;
	int		len;

	len = calculate_expanded_length(str, pid);
	expanded = malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			ft_strcpy(&expanded[j], pid);
			j += ft_strlen(pid);
			i += 2;
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
