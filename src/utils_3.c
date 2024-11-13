/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:55:43 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/13 18:12:27 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	to_quotes_unmatched(t_token **head, t_token **curr)
{
	t_token	*token;
	char	*content;

	printf("Error: Unmatched quotes.\n");
	content = ft_strdup("unmatched");
	token = new_token(UNMATCHED, content);
	free(content);
	add_token_node(head, curr, &token);
}

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

void	expand_and_add_arg(t_cmd *cmd, char *expanded_value)
{
	char	**split_args;
	int		i;
	char	*arg_copy;

	i = 0;
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
