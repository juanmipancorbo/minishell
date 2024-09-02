/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/02 22:53:45 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* ************************************************************************** */
/*                                      DEFINES                               */
/* ************************************************************************** */
# define MALLOC_E "Malloc error\n"

/* ************************************************************************** */
/*                                 OPCODE / STRUCTS                           */
/* ************************************************************************** */
typedef enum e_tkn_type
{
	WORD,
	PIPE,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	SINGLE_Q,
	DOUBLE_Q,
	VAR,
}							t_tkn_type;

typedef struct s_token
{
	t_tkn_type		type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}							t_token;

typedef struct s_general
{
	t_token	*tokens;
	char	**env_var;
}							t_general;

typedef struct s_process
{
	char	*argv;
}							t_process;

// typedef struct s_cmd
// {
// 	char			**args;
// 	char			*in_rd;
// 	char			*out_rd;
// 	int				append;
// 	struct s_cmd	*next;
// }							t_cmd;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

int		ft_isspace(char c);
t_token	*new_token(t_tkn_type type, char *value);
void	add_token_node(t_token **head, t_token **curr, t_token **token);
char	*to_q_content(const char **input, char q_type);
void	to_variable(const char **input, t_token **head, t_token **curr);
t_token	*to_tokenize(const char *input);

//execution
void	dup_env_variables(t_general *data, char **env);
void	manage_error(char *msg, t_general *data);

#endif