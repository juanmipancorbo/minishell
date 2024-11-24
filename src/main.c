/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/24 11:38:03 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

static void	clean_loop(char *input, t_token *tokens, t_cmd *cmds)
{
	t_token	*temp;

	free(input);
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
	char	cwd[VALUE_BUFFER];

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
	{
		getcwd(cwd, sizeof(cwd));
		*path = ft_strdup(cwd);
	}
	free(temp);
	if (!ft_strlen(*machine) || !ft_strlen(*path) || !ft_strlen(*user))
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
	{
		to_free_four(user, machine, path, NULL);
		return (NULL);
	}
	len = ft_strlen(user) + ft_strlen(machine) + ft_strlen(path) + 8;
	prompt = malloc(len);
	if (!prompt)
		return (NULL);
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
		prompt = NULL;
		if (to_env_list_size(utils->env_var) > 10)
			prompt = to_prompt(utils->env_var);
		if (!prompt)
			prompt = ft_strdup("minishell> ");
		input = readline(prompt);
		free(prompt);
		if (input)
			add_history(input);
		to_check_input(&input);
		input = incomplete_pipe(input);
		tokens = to_tokenize(input);
		cmds = to_parse(&tokens, utils);
		if (input && tokens)
			init_execution(&cmds, utils);
		clean_loop(input, tokens, cmds);
	}
	free_env_copy(utils);
}

int	main(int argc, char **argv, char **env)
{
	t_utils		utils;

	(void)argv;
	(void)argc;
	if (argc == 1)
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
	else
		check_arg(argv);
	return (0);
}
