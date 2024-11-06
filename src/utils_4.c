/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:00:32 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/06 12:01:29 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int ft_size(int i)
{
	int count;
	
	while(i > 0)
	{	
		count++;
		i = i/10;
	}
	return(count);
}

char *ft_itoa(int nb)
{
	char *str;
	int i;
	
	i = ft_size(nb);
	str = malloc(sizeof(int) * i + 1);
	if (!str)
		manage_error("Error:");
	str[i] = '\0';
	while(nb > 0)
	{
		str[--i] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}