/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:18:21 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/21 13:20:19 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*complete_pipe(char *input)
{
	char	*input_2;
	char	*newinput;

	while (1)
	{
		input_2 = readline(">");
		if (!input_2)
		{
			printf("minishell: syntax error: unexpected end of file\n");
			g_exit_code = 2;
			free(input);
			free(input_2);
			return (NULL);
		}
		if (input_2[0] != '\0')
		{
			newinput = ft_strjoin(input, input_2);
			free(input);
			free(input_2);
			return (newinput);
		}
	}
}

char	*incomplete_pipe(char *input)
{
	int	i;

	if (!input)
		return (NULL);
	i = ft_strlen(input) - 1;
	while (ft_isspace(input[i]))
		i--;
	if ((input[i] == '|' && input[i - 1] == '|') || input[i] != '|')
		return (input);
	if ((input[i] == '|' && input[i - 1] != '|'))
		return (complete_pipe(input));
	return (input);
}
