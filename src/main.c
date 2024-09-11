/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/11 20:44:34 by jpancorb         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_utils		data;

	if (argc == 1)
	{
		ft_memset(&data, 0, sizeof(data));
		dup_env_variables(&data, env);
		print_var(data.env_var);
		init_loop(argv);
	}
	free_env_copy(data.env_var);
	return (0);
}
