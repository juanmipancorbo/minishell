/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/17 19:24:17 by jpancorb         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_utils		data;

	if (argc == 1)
	{
		ft_memset(&data, 0, sizeof(data));
		dup_env_variables(&data, env);
	//	print_var(data.env_var);
		init_loop(argv, env);
	}
	free_env_copy(data.env_var);
	return (0);
}
