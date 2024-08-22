/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:45:45 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 17:38:03 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*un_str1;
	unsigned char	*un_str2;
	size_t			i;

	un_str1 = (unsigned char *)s1;
	un_str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (un_str1[i] != un_str2[i])
			return (un_str1[i] - un_str2[i]);
		i++;
	}
	return (0);
}
