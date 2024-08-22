/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:35:56 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:06:59 by jpancorb         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	dstl;
	size_t	srcl;

	i = 0;
	dstl = sft_strlen(dst);
	y = dstl;
	srcl = sft_strlen(src);
	if (dstsize == 0 || dstsize <= dstl)
		return (srcl + dstsize);
	while (src[i] && i < (dstsize - dstl - 1))
		dst[y++] = src[i++];
	dst[y] = 0;
	return (dstl + srcl);
}
