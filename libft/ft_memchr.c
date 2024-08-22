/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:35:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 17:32:20 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*un_str;

	i = 0;
	un_str = (unsigned char *)s;
	while (i < n)
		if (un_str[i++] == (unsigned char)c)
			return (&un_str[--i]);
	return (NULL);
}
