/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:15:45 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:31:15 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	y;
	char	*subs;

	i = 0;
	y = 0;
	while (s[y])
		y++;
	if (y < start)
		len = 0;
	if (len > y - start)
		len = y - start;
	subs = malloc((sizeof(char) * len + 1));
	if (!subs)
		return (NULL);
	while (start < y && i < len)
		subs[i++] = s[start++];
	subs[i] = 0;
	return (subs);
}
