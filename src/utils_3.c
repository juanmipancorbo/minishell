/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:55:43 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/28 20:31:03 by jpancorb         ###   ########.fr       */
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

char	*process_token_value(char *value, t_utils *utils)
{
	char	*result;
	char	*temp;
	size_t	i;
	size_t	j;
	int		in_single_quote;
	int		in_double_quote;

	result = malloc(ft_strlen(value) + 1); // Asegúrate de tener espacio suficiente
	if (!result)
		manage_error("Malloc error (process_token_value).");

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !in_double_quote) // Comienza o termina una comilla simple
			in_single_quote = !in_single_quote;
		else if (value[i] == '"' && !in_single_quote) // Comienza o termina una comilla doble
			in_double_quote = !in_double_quote;
		else if (value[i] == '$' && in_double_quote && ft_isalnum(value[i + 1])) // Expansión de variables dentro de comillas dobles
		{
			temp = expand_var(value + i + 1, utils->env_var); // Expande la variable
			if (temp)
			{
				ft_strcpy(&result[j], temp); // Copia la variable expandida
				j += ft_strlen(temp);
				i += ft_strlen(temp); // Avanza el índice según el largo de la variable expandida
				free(temp);
			}
		}
		else // Copia el carácter normal si no es una comilla o no estamos expandiendo
			result[j++] = value[i];
		i++;
	}
	result[j] = '\0'; // Termina la cadena resultante
	free(value); // Liberamos la cadena original
	return (result);
}

void	expand_and_add_arg(t_cmd *cmd, char *expanded_value)
{
	char	**split_args;
	int		i;

	// Usa ft_split para separar el valor expandido por espacios
	split_args = ft_split(expanded_value, ' ');
	if (!split_args)
		return ;

	// Añade cada palabra como un argumento separado
	i = 0;
	while (split_args[i])
	{
		add_arg(cmd, split_args[i]);
		i++;
	}

	// Libera la memoria
	// i = 0;
	// while (split_args[i])
	// 	free(split_args[i++]);
	// free(split_args);
}

