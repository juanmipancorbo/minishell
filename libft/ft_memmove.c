/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:16:56 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 17:44:18 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (d < s || d >= (s + len))
		while (len--)
			*d++ = *s++;
	else
	{
		d += len;
		s += len;
		while (len--)
			*(--d) = *(--s);
	}
	return (dst);
}
