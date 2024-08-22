/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:18:23 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:26:39 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static size_t	sft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_charset(s1[start], set))
		start++;
	end = sft_strlen(s1);
	while (end > start && ft_charset(s1[end - 1], set))
		end--;
	trimed = malloc((end - start + 1) * sizeof(char));
	if (!trimed)
		return (NULL);
	i = 0;
	while (start < end)
		trimed[i++] = s1[start++];
	trimed[i] = 0;
	return (trimed);
}
