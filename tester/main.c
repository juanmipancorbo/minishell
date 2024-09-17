/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/03 17:34:52 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

static void	print_var(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

static void	init_loop(char **argv)
{
	char	*input;
	t_token	*tokens;
	t_token	*temp;

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
		free(input);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp->value);
			free(temp);
		}
	}
}

// tester main
int	main(int argc, char **argv, char **env)
{
	t_cmd cmd;
	t_utils	data;

	char *path = "./test1";
	char *path2 = "./test2";

	set_file_descriptor(&cmd,path2,RD_IN);
	set_file_descriptor(&cmd,path,RD_OUT);
	//set_file_descriptor(&cmd,path2,RD_OUT);

	//char *arg[3]={"/bin/ls", "-a", NULL};
	char *arg[3]={"/bin/wc", "-l", NULL};
	cmd.args = arg;
	cmd.full_path = arg[0];
	data.env_var = env;

	init_execution(&cmd,&data);
}