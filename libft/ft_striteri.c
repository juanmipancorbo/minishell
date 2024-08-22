/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:35:17 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:05:06 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
