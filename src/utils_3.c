/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:55:43 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 11:54:15 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_env_name(char *var_name, t_utils *utils, int env)
{
	int		i;
	char	**env_var;
	size_t	var_len;

	i = 0;
	if (env == 1)
		env_var = utils->env_var;
	if (env == 2)
		env_var = utils->export_var;
	var_len = ft_strlen(var_name);
	while (env_var && env_var[i])
	{
		if (!ft_strncmp(env_var[i], var_name, var_len))
			return (0);
		i++;
	}
	return (-1);
}

static size_t	handle_quotes_and_expand(char *value, char *result,
	t_expand_data *data, t_utils *utils)
{
	char	*temp;

	if (value[data->i] == '\'' && !data->in_double_quote)
		data->in_single_quote = !data->in_single_quote;
	else if (value[data->i] == '"' && !data->in_single_quote)
		data->in_double_quote = !data->in_double_quote;
	else if (value[data->i] == '$' && data->in_double_quote
		&& ft_isalnum(value[data->i + 1]))
	{
		temp = expand_var(value + data->i + 1, utils->env_var);
		if (temp)
		{
			ft_strcpy(&result[data->j], temp);
			data->j += ft_strlen(temp);
			data->i += ft_strlen(temp);
			free(temp);
		}
	}
	else
		result[(data->j)++] = value[data->i];
	return (data->i);
}

char	*process_token_value(char *value, t_utils *utils)
{
	char			*result;
	t_expand_data	data;

	result = malloc(ft_strlen(value) + 1);
	if (!result)
		exit_error(MALLOC_E, 10);
	data.i = 0;
	data.j = 0;
	data.in_single_quote = 0;
	data.in_double_quote = 0;
	while (value[data.i])
	{
		data.i = handle_quotes_and_expand(value, result, &data, utils);
		data.i++;
	}
	result[data.j] = '\0';
	free(value);
	return (result);
}

int	is_only_spaces(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
