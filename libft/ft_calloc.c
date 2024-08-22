/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:13:05 by jpancorb          #+#    #+#             */
/*   Updated: 2023/10/06 17:21:22 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = s;
	i = 0;
	while (i < n)
		c[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	sft_bzero(mem, (count * size));
	return (mem);
}
