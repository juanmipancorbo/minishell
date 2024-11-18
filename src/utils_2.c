/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:16:38 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/18 19:51:15 by jpancorb         ###   ########.fr       */
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
			result = (char *)malloc(strlen(src) - i + 2);
			if (!result)
				return (NULL);
			result[j++] = '~';
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
	{
		free(old_str);
		old_str = NULL;
	}
	old_str = new_str;
	return (old_str);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	len;
	char	*newstr;

	i = 0;
	y = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (s1[i])
		newstr[i++] = s1[y++];
	i = 0;
	while (s2[i])
		newstr[y++] = s2[i++];
	newstr[y] = 0;
	free(s1);
	return (newstr);
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
