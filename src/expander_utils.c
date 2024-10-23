/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:00:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/23 18:36:26 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_dollars(const char *value, t_utils *utils)
{
	char	*result;
	char	*var_value;
	char	*temp;
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
			temp = utils->pid;
			while (*temp)
				result[j++] = *temp++;
			i += 2;
		}
		else if (value[i] == '$' && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			i++;
			int start = i;
			while (ft_isalnum(value[i]) || value[i] == '_')
				i++;
			temp = ft_strndup(&value[start], i - start);
			var_value = get_env_value(utils->env_var, temp);
			free(temp);
			if (var_value)
				while (*var_value)
					result[j++] = *var_value++;
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}
