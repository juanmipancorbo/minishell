/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:56:53 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/23 17:31:24 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_next_valid(const char *input, int *i)
{
	(*i)++;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|' || (input[*i] == '<'
			|| input[*i] == '>'))
		return (0);
	return (1);
}

static void	print_syntax_error(char c)
{
	if (c == '\0')
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	g_exit_code = 2;
}

static t_bool	check_redirection_sequence(const char *input, int *i)
{
	int	count;

	count = 1;
	while (input[*i] == input[*i + 1] && (input[*i] == '<' || input[*i] == '>'))
	{
		count++;
		(*i)++;
		if (count > 2)
			return (FALSE);
	}
	if (!check_next_valid(input, i))
		return (FALSE);
	return (TRUE);
}

void	to_check_input(char **input)
{
	int		i;
	char	last_char;

	i = 0;
	last_char = 0;
	if (!*input)
		exit_error("exit\n", g_exit_code);
	while ((*input)[i])
	{
		if ((*input)[i] == '<' || (*input)[i] == '>')
		{
			if (!check_redirection_sequence(*input, &i))
			{
				print_syntax_error((*input)[i]);
				free(*input);
				*input = NULL;
				return ;
			}
		}
		last_char = (*input)[i];
		i++;
	}
}
