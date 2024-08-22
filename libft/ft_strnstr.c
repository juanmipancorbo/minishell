/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:00:34 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:20:33 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	size_t	i;
	size_t	y;

	h = (char *)haystack;
	i = 0;
	y = 0;
	if (!needle[i])
		return (h);
	while (h[i] && i < len)
	{
		while (h[i + y] == needle[y] && h[i + y])
		{
			if (!needle[++y])
				return (&h[i]);
			if (i + y >= len)
				break ;
		}
		i++;
		y = 0;
	}
	return (NULL);
}
