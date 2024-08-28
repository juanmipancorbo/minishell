/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:23:23 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/28 06:59:37 by jpancorb         ###   ########.fr       */
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

static char	*sft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dst;

	len = sft_strlen(s1);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	sft_strcpy(dst, s1);
	return (dst);
}
