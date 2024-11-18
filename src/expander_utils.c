/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:00:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/18 22:22:02 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	to_expand_pid(char *result, int j, t_utils *utils)
{
	char	*temp;

	temp = utils->pid;
	if (temp)
		while (*temp)
			result[j++] = *temp++;
	return (j);
}

static int	to_expand_var(char *result, const char *value, int *i,
	t_utils *utils)
{
	char	*temp;
	char	*var_value;
	int		j;
	int		start;

	j = 0;
	(*i)++;
	start = *i;
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	temp = ft_strndup(&value[start], *i - start);
	var_value = get_env_value(utils->env_var, temp);
	free(temp);
	if (var_value)
		while (*var_value)
			result[j++] = *var_value++;
	result[j] = '\0';
	return (j);
}

static int	to_expand_exit_code(char *result, int j)
{
	char	*temp;

	temp = ft_itoa(g_exit_code);
	if (temp)
		while (*temp)
			result[j++] = *temp++;
	free (temp);
	return (j);
}

static int	handle_dollar_expansion(char *result, const char *value, int *i,
	t_utils *utils)
{
	int	j;

	j = 0;
	if (value[*i] == '$' && value[*i + 1] == '$')
	{
		j = to_expand_pid(result, j, utils);
		*i += 2;
	}
	else if (value[*i] == '$' && value[*i + 1] == '?')
	{
		j = to_expand_exit_code(result, j);
		*i += 2;
	}
	else if (value[*i] == '$' && (ft_isalnum(value[*i + 1])
			|| value[*i + 1] == '_'))
		j = to_expand_var(result, value, i, utils);
	return (j);
}

char	*expand_dollars(const char *value, t_utils *utils)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * VALUE_BUFFER);
	if (!result)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '$')
		{
			len = handle_dollar_expansion(result + j, value, &i, utils);
			j += len;
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}
