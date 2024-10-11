/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:00:50 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/11 18:44:47 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	calculate_expanded_length(const char *str, const char *pid)
// {
// 	int	i;
// 	int	len;
// 	int	pid_len;

// 	i = 0;
// 	len = 0;
// 	pid_len = ft_strlen(pid);
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '$')
// 		{
// 			len += pid_len;
// 			i += 2;
// 		}
// 		else
// 		{
// 			len++;
// 			i++;
// 		}
// 	}
// 	return (len);
// }

// char	*expand_dollars(const char *str, t_utils *utils)
// {
// 	char	*expanded;
// 	int		i;
// 	int		j;
// 	int		len;

// 	len = calculate_expanded_length(str, utils->pid);
// 	expanded = malloc(sizeof(char) * (len + 1));
// 	if (!expanded)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '$')
// 		{
// 			ft_strcpy(&expanded[j], utils->pid);
// 			j += ft_strlen(utils->pid);
// 			i += 2;
// 		}
// 		else
// 			expanded[j++] = str[i++];
// 	}
// 	expanded[j] = '\0';
// 	return (expanded);
// }

// char	*expand_dollars(const char *value, t_utils *utils)
// {
// 	char	*expanded;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	len = ft_strlen(value);

// 	if (value[i++] == '$')
// 		expanded = expand_var((char *)value, utils->env_var);
// 	else
// 	{
// 		while (value[i])
// 		{
// 			if (!ft_isspace(value[i]) && value[i] != '|' && value[i] != '<'
// 				&& value[i] != '>' && value[i] != '"' && value[i] != '$')
// 				i++;
// 			if (value[i] == '$')
// 				expanded = expand_var((char *)value, utils->env_var);
// 		}
// 	}
// 	return (expanded);
// }

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
