/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:18:21 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/20 14:13:57 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
char *complete_pipe(char *input)
{
	char *input_2;
	char *newinput;

	while (1)
	{
		input_2=readline(">");
		if (input_2[0] != '\0')
		{
			newinput = ft_strjoin(input , input_2);
			free(input);
			free(input_2);
			return (newinput);
		}
	}
	
}


char *incomplete_pipe(char *input)
{
	int i;

	i = ft_strlen(input) - 1;
	while (ft_isspace(input[i--]));
	if ((input[i] == '|' && input[i - 1] == '|') || input[i] != '|')
		return (input);
	if ((input[i] == '|' && input[i - 1] != '|'))
		return (complete_pipe(input));
}