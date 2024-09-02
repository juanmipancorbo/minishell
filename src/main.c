/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/02 17:31:54 by jpancorb         ###   ########.fr       */
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

static void	init_loop(t_general *data, char**argv, char **env)
{
	char	*input;
	t_token	*tokens;
	t_token	*temp;

	(void)data;
	(void)argv;
	(void)env;
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

int	main(int argc, char **argv, char **env)
{
	t_general	data;
	
	if (argc == 1)
	{
		ft_memset(&data, 0 , sizeof(data));
		dup_env_variables(&data,env);
		init_loop(&data,argv,env);
	}
	return (0);
}
