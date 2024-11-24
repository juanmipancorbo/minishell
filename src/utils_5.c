/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:18:21 by apaterno          #+#    #+#             */
/*   Updated: 2024/11/24 11:42:18 by apaterno         ###   ########.fr       */
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
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
				STDERR_FILENO);
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
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|' && input[i + 1] != '|')
		return (free(input), ft_strdup("|"));
	i = ft_strlen(input) - 1;
	while (ft_isspace(input[i]))
		i--;
	if ((input[i] == '|' && input[i - 1] == '|') || input[i] != '|')
		return (input);
	if (input[i] == '|')
		return (complete_pipe(input));
	return (input);
}

void	expand_and_add_arg(t_cmd *cmd, char *expanded_value)
{
	char	**split_args;
	int		i;
	char	*arg_copy;

	i = 0;
	if (is_only_spaces(expanded_value))
		add_arg(cmd, ft_strdup(" "));
	split_args = ft_split(expanded_value, ' ');
	if (!split_args)
		return ;
	while (split_args[i])
	{
		arg_copy = ft_strdup(split_args[i]);
		if (!arg_copy)
			break ;
		add_arg(cmd, arg_copy);
		i++;
	}
	i = 0;
	while (split_args[i])
		free(split_args[i++]);
	free(split_args);
}

t_bool	fill_fd(t_cmd *cmd)
{
	t_red	*in_rd;
	t_red	*out_rd;

	in_rd = cmd->in_rd;
	out_rd = cmd->out_rd;
	while (out_rd)
	{
		if (!set_file_descriptor(out_rd))
			return (FALSE);
		out_rd = out_rd->next;
	}
	while (in_rd)
	{
		if (!set_file_descriptor(in_rd))
			return (FALSE);
		in_rd = in_rd->next;
	}
	return (TRUE);
}

int	ft_printf_fd(const char *str, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == 's')
				ft_putstr_fd(va_arg(ap, char *), STDERR_FILENO);
			else if (str[i] == 'c')
				ft_putchar_fd(va_arg(ap, int), STDERR_FILENO);
		}
		else
		{
			write(2, &str[i], 1);
		}
		i++;
	}
	va_end(ap);
	return (1);
}
