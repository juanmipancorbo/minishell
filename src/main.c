/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/20 17:57:11 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_loop(char **argv, char **env)
{
	char	*input;
	t_token	*tokens;
	t_token	*temp;
	t_cmd	*cmds;

	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = to_tokenize(input);
		print_tokens(tokens);
		cmds = to_parse(tokens, env);
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
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_utils		data;

// 	if (argc == 1)
// 	{
// 		ft_memset(&data, 0, sizeof(data));
// 		dup_env_variables(&data, env);
// 		print_var(data.env_var);
// 		init_loop(argv, env);
// 	}
// 	free_env_copy(data.env_var);
// 	return (0);
// }
t_cmd	*cmd_addnewnode(char **argv , char *full_path);
void	dlstadd_back(t_cmd **cmd, t_cmd *node);

int	main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	t_utils utils;

	char *arg1[3]={"/bin/ls", "-a", NULL};
	//char *arg2[3]={"/bin/wc", "-l", NULL};
	cmd = NULL;
	utils.env_var = env;
	
	dlstadd_back(&cmd,cmd_addnewnode(arg1,arg1[0]));
	//dlstadd_back(&cmd,cmd_addnewnode(arg2,arg2[0]));
	init_execution(&cmd, &utils);
	return (0);
}