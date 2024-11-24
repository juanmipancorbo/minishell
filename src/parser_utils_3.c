/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:43:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 18:43:23 by jpancorb         ###   ########.fr       */
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

void	to_word_export(const char **input, t_token **head, t_token **curr)
{
	const char	*start;
	char		*value;
	t_token		*token;
	size_t		len;

	while (ft_isspace(**input))
		(*input)++;
	start = *input;
	while (**input && **input != '|' && !ft_isspace(**input))
		(*input)++;
	len = *input - start;
	value = ft_strndup(start, len);
	if (!value)
		exit_error(MALLOC_E, 10);
	token = new_token(WORD, value);
	free(value);
	add_token_node(head, curr, &token, input);
}

int	to_process_export(char *head_value, const char *input)
{
	char	*temp;
	int		i;

	i = 0;
	while (ft_isspace(*input))
		input++;
	if (!ft_strncmp(head_value, "export", 6) && ft_strchr(input, '='))
	{
		while (input[i] && input[i] != ' ' && input[i] != '=')
			i++;
		temp = (char *)malloc(sizeof(char) * (i + 1));
		if (!temp)
			return (0);
		i = 0;
		while (*input && *input != ' ' && *input != '|' && *input != '=')
			temp[i++] = *input++;
		temp[i] = '\0';
		if (ft_strchr(temp, '\'') || ft_strchr(temp, '"'))
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	return (0);
}

void	to_remove_quotes(char **value)
{
	char	*new_value;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!value || !*value)
		return ;
	len = ft_strlen(*value);
	new_value = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_value)
		exit_error(MALLOC_E, 10);
	i = 0;
	j = 0;
	while ((*value)[i])
	{
		if ((*value)[i] != '"')
			new_value[j++] = (*value)[i];
		i++;
	}
	new_value[j] = '\0';
	free(*value);
	*value = new_value;
}
