/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/13 13:26:19 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

static void	clean_loop(char *input, t_token *tokens, t_cmd *cmds)
{
	t_token	*temp;

	free(input);
	// if (utils->pid)
	// {
	// 	free(utils->pid);
	// 	utils->pid = NULL;
	// }
	// if (utils->process_id)
	// {
	// 	free(utils->process_id);
	// 	utils->process_id = NULL;
	// }
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	free_cmds(cmds);
}

static int	build_prompt_parts(char **env_var, char **user, char **machine,
	char **path)
{
	char	*temp;

	temp = expand_var("SESSION_MANAGER", env_var);
	*machine = malloc(8);
	if (!*machine)
		return (0);
	ft_strlcpy(*machine, (strchr(temp, '/')) + 1, 8);
	*path = expand_var("PWD", env_var);
	temp = replace_str(temp, expand_var("HOME", env_var));
	*path = replace_str(*path, copy_after_str(*path, temp));
	*user = expand_var("USER", env_var);
	if (!*path)
		*path = expand_var("PWD", env_var);
	if (!*user || !*machine || !*path)
		return (0);
	free(temp);
	return (1);
}

static char	*to_prompt(char **env_var)
{
	char	*prompt;
	char	*user;
	char	*machine;
	char	*path;
	size_t	len;

	if (to_env_list_size(env_var) < 10)
		return ("minishell> \0");
	if (!build_prompt_parts(env_var, &user, &machine, &path))
		return ("minishell> \0");
	len = strlen(user) + strlen(machine) + strlen(path) + 8;
	prompt = malloc(len);
	if (!prompt)
		return ("minishell> \0");
	*prompt = '\0';
	ft_strlcat(prompt, user, len);
	ft_strlcat(prompt, "@", len);
	ft_strlcat(prompt, machine, len);
	ft_strlcat(prompt, ":", len);
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
		if (to_env_list_size(utils->env_var) > 10)
			free(prompt);
		if (!input)
			exit_error("Exit\n", g_exit_code);
		if (*input)
			add_history(input);
		tokens = to_tokenize(input);
		cmds = to_parse(tokens, utils);
		// print_tokens(tokens);
		// print_cmds(cmds);
		if (*input && tokens && tokens->type != UNMATCHED)
			init_execution(&cmds, utils);
		clean_loop(input, tokens, cmds);
	}
	free_env_copy(utils);
}

int	main(int argc, char **argv, char **env)
{
	t_utils		utils;

	if (argc >= 1 && argv[0])
	{
		if (env && !(*env))
		{
			init_signals(1);
			to_no_env(&utils);
		}
		else
		{
			init_signals(1);
			dup_env_variables(&utils, 1, env, &utils.env_var);
		}
		init_loop(&utils);
	}
	return (0);
}
