/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:16:38 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/01 18:59:15 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*copy_after_str(const char *src, const char *target)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (strncmp(&src[i], target, strlen(target)) == 0)
		{
			i += strlen(target);
			result = (char *)malloc(strlen(src) - i + 1);
			if (!result)
				return (NULL);
			while (src[i])
				result[j++] = src[i++];
			result[j] = '\0';
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*replace_str(char *old_str, char *new_str)
{
	if (old_str)
		free(old_str);
	old_str = new_str;
	return (old_str);
}

void	to_free_four(char *a, char *b, char *c, char *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}

void	free_q(t_token **curr, t_token **end)
{
	*end = *curr;
	*curr = (*curr)->next;
	free((*end)->value);
	free(*end);
}
