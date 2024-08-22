/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:30:38 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 21:20:26 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_splitcount(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	while (i < n)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_freeall(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	s_end;
	size_t	s_start;
	size_t	splitcount;

	i = 0;
	s_end = 0;
	splitcount = ft_splitcount(s, c);
	res = malloc(sizeof(char *) * (splitcount + 1));
	if (!res)
		return (NULL);
	while (i < splitcount && *s)
	{
		while (s[s_end] == c)
			s_end++;
		s_start = s_end;
		while (s[s_end] != c && s[s_end])
			s_end++;
		res[i] = ft_strndup(&s[s_start], s_end - s_start);
		if (!res[i++])
			return (ft_freeall(res));
	}
	res[i] = 0;
	return (res);
}
