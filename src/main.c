/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/16 17:16:46 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_loop(char *input, t_token *tokens, t_cmd *cmds, int *pid)
{
	t_token	*temp;

	free(input);
	free(pid);
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
	//	printf("Free token value.\n");
		free(temp);
	}
	free_cmds(cmds);
	delete_herdocf();
}

static int	build_prompt_parts(char **env_var, char **user, char **machine,
	char **path)
{
	char	*temp;

	*user = expand_var("USER", env_var);
	temp = expand_var("SESSION_MANAGER", env_var);
	*machine = malloc(8);
	if (!*machine)
		return (0);
	ft_strlcpy(*machine, (strchr(temp, '/')) + 1, 8);
	*path = expand_var("PWD", env_var);
	temp = replace_str(temp, expand_var("HOME", env_var));
	*path = replace_str(*path, copy_after_str(*path, temp));
	free(temp);
	if (!*user || !*machine || !*path)
		return (0);
	return (1);
}

static char	*to_prompt(char **env_var)
{
	char	*prompt;
	char	*user;
	char	*machine;
	char	*path;
	size_t	len;

	if (!build_prompt_parts(env_var, &user, &machine, &path))
		return (NULL);
	len = strlen(user) + strlen(machine) + strlen(path) + 9;
	prompt = malloc(len);
	if (!prompt)
		return (NULL);
	*prompt = '\0';
	ft_strlcat(prompt, user, len);
	ft_strlcat(prompt, "@", len);
	ft_strlcat(prompt, machine, len);
	ft_strlcat(prompt, ":~", len);
	ft_strlcat(prompt, path, len);
	ft_strlcat(prompt, "$ ", len);
	to_free_four(user, machine, path, NULL);
	return (prompt);
}

static void	init_loop(t_utils *utils)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		prompt = to_prompt(utils->env_var);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = to_tokenize(input);
		// print_tokens(tokens);
		cmds = to_parse(tokens, utils);
		// print_cmds(cmds);
		if (*input && cmds != NULL)
			init_execution(&cmds, utils);
		clean_loop(input, tokens, cmds, utils->process_id);
	}
	free_env_copy(utils->env_var);
}

int	main(int argc, char **argv, char **env)
{
	t_utils		utils;

	if (argc >= 1 && argv[0])
	{
		init_signals(1);
		dup_env_variables(&utils, env);
		init_loop(&utils);
	}
	return (0);
}
