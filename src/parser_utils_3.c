/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:43:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 11:46:54 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_check_quotes(char **input)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'')
			single_q++;
		else if ((*input)[i] == '"')
			double_q++;
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		write(2, "error: unmatched quotes\n", 24);
		return (-1);
	}
	return (0);
}
