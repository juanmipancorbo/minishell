/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:17:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 17:23:50 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n && ++i)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*res;

	len = ft_numlen(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	if (n == 0)
		res[0] = '0';
	if (n < 0)
		res[0] = '-';
	while (n)
	{
		if (n > 0)
			res[--len] = 48 + (n % 10);
		else
			res[--len] = 48 + (n % 10) * -1;
		n /= 10;
	}
	return (res);
}
