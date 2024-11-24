/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:56:53 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 12:56:51 by jpancorb         ###   ########.fr       */
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
		ft_putstr_fd("-minishell: syntax error near unexpected token\
`newline'\n", STDERR_FILENO);
	else
		ft_printf_fd("-minishell: syntax error near unexpected token `%c'\n",
			c);
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

static int	to_check_pipe(char **input)
{
	int	i;

	i = 0;
	if ((*input)[0] == '|' && !(*input)[1])
		error_msg("minishell: syntax error near unexpected token `|'", 2);
	while ((*input)[i])
	{
		if ((*input)[i] == '|' && (*input)[i + 1] == '|')
		{
			write(2, "error: \"||\" operator not implemented\n", 38);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	to_check_input(char **input)
{
	int		i;

	i = 0;
	if (!*input)
		exit_error("exit\n", g_exit_code);
	if (to_check_quotes(input) || to_check_pipe(input))
	{
		free(*input);
		*input = NULL;
		return ;
	}
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
		i++;
	}
}
