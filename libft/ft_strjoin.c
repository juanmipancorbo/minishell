/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:14:06 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:08:16 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	len;
	char	*newstr;

	i = 0;
	y = 0;
	len = sft_strlen(s1) + sft_strlen(s2);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (s1[i])
		newstr[i++] = s1[y++];
	i = 0;
	while (s2[i])
		newstr[y++] = s2[i++];
	newstr[y] = 0;
	return (newstr);
}
