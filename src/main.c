/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/27 17:00:57 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	to_free_all(char *a, char *b, char *c, char *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}

static char	*copy_after_str(const char *src, const char *target)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (strncmp(&src[i], target, strlen(target)) == 0)
		{
			i += strlen(target);
			result = (char *)malloc(strlen(src) - i + 1);
			if (!result)
				return (NULL);
			while (src[i])
				result[j++] = src[i++];
			result[j] = '\0';
			return (result);
		}
		i++;
	}
	return (NULL);
}

static char	*to_prompt(char **env_var)
{
	char	*prompt;
	char	*user;
	char	*machine;
	char	*path;
	char	*temp;

	user = expand_var("USER", env_var);
	temp = expand_var("SESSION_MANAGER", env_var);
	machine = malloc(8);
	ft_strlcpy(machine, (strchr(temp, '/')) + 1, 8);
	machine[7] = '\0';
	path = expand_var("PWD", env_var);
	temp = expand_var("HOME", env_var);
	path = copy_after_str(path, temp);
	prompt = malloc(strlen(user) + strlen(machine) + strlen(path) + 4);
	if (!prompt)
		return (NULL);
	ft_strlcat(prompt, user, strlen(user) + 1);
	ft_strlcat(prompt, "@", strlen(prompt) + 2);
	ft_strlcat(prompt, machine, strlen(prompt) + strlen(machine) + 1);
	ft_strlcat(prompt, ":~", strlen(prompt) + 3);
	ft_strlcat(prompt, path, strlen(prompt) + strlen(path) + 1);
	ft_strlcat(prompt, "$ ", strlen(prompt) + 3);
	to_free_all(user, machine, path, temp);
	return (prompt);
}

static void	init_loop(char **argv, t_utils *data)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;
	t_token	*temp;
	t_cmd	*cmds;

	(void)argv;
	prompt = to_prompt(data->env_var);
	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = to_tokenize(input);
		print_tokens(tokens);
		cmds = to_parse(tokens, data->env_var);
		// init_execution
		// funcion clean_exit
		print_cmds(cmds);
		free(input);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp->value);
			free(temp);
		}
		free_cmds(cmds);
	}
	free_env_copy(data->env_var);
}

int	main(int argc, char **argv, char **env)
{
	t_utils		data;

	if (argc == 1)
	{
		ft_memset(&data, 0, sizeof(data));
		dup_env_variables(&data, env);
		print_var(data.env_var);
		init_loop(argv, &data);
	}
	return (0);
}

