/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:02:54 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/27 21:26:42 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_token	*temp;

	while (1)
	{
		//input = readline("minishell> ");
		input = strdup("ls -l");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = to_tokenize(input);
		//printf("Input: %s\n", input);
		printf("to_tokenize DONE.\n");
		print_tokens(tokens);
		printf("print_tokens DONE.\n");
		free(input);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp->value);
			free(temp);
		}
	}
	return (0);
}
