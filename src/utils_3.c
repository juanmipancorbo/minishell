/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:55:43 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/29 20:04:22 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	to_get_pid(t_utils *utils)
{
	int		fd;
	int		bytes_read;
	char	buffer[256];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return ;
	bytes_read = read(fd, buffer, 255);
	if (bytes_read == -1)
	{
		close(fd);
		return ;
	}
	buffer[bytes_read] = '\0';
	parse_pid(utils, buffer);
	close(fd);
}

int	check_export_name(char *var_name, t_utils *utils)
{
	int		i;
	char	**env;
	size_t	var_len;

	i = 0;
	env = utils->export_var;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, var_len))
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
		manage_error("Malloc error (process_token_value).");

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
	char	*arg_copy;
	int		i;

	split_args = ft_split(expanded_value, ' ');
	if (!split_args)
		return ;
	i = 0;
	while (split_args[i])
	{
		arg_copy = ft_strdup(split_args[i]);
		if (!arg_copy)
		{
			while (split_args[i])
				free(split_args[i++]);
			free(split_args);
			return ;
		}
		add_arg(cmd, arg_copy);
		i++;
	}
	i = 0;
	while (split_args[i])
		free(split_args[i++]);
	free(split_args);
}

// void	expand_and_add_arg(t_cmd *cmd, char *expanded_value)
// {
// 	char	**split_args;
// 	int		i;

// 	i = 0;
// 	split_args = ft_split(expanded_value, ' ');
// 	if (!split_args)
// 		return ;
// 	while (split_args[i])
// 	{
// 		add_arg(cmd, split_args[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (split_args[i])
// 		free(split_args[i++]);
// 	free(split_args);
// }
