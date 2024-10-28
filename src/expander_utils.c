/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:00:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/28 20:57:30 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	to_expand_pid(char *result, int j, t_utils *utils)
{
	char	*temp;

	temp = utils->pid;
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
	return (j);
}

char	*expand_dollars(const char *value, t_utils *utils)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (strlen(value) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '$')
		{
			j = to_expand_pid(result, j, utils);
			i += 2;
		}
		else if (value[i] == '$' && (ft_isalnum(value[i + 1])
				|| value[i + 1] == '_'))
			j += to_expand_var(result + j, value, &i, utils);
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}
