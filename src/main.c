/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/26 17:03:54 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_loop(char **argv, t_utils *data)
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
		cmds = to_parse(tokens, data->env_var);
		// init_execution
		// funcion clean_exit
		print_cmds(cmds);
		free(input);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
		//	free(temp->value);
			free(temp);
		}
		free_cmds(cmds);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_utils		data;

	if (argc == 1)
	{
		ft_memset(&data, 0, sizeof(data));
		dup_env_variables(&data, env);
	//	print_var(data.env_var);
		init_loop(argv, &data);
	}
	//free_env_copy(data.env_var);
	return (0);
}
