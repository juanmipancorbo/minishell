/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/03 17:39:10 by apaterno         ###   ########.fr       */
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


typedef struct s_utils
{
	char	**env_var;
}							t_utils;


typedef struct s_red
{
	char			*name;
	int				fd;
	struct s_red	*next;
}							t_red;

typedef struct s_cmd
{
	char			**args;
	char			*full_path;	
	t_red			*in_rd;
	t_red			*out_rd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}							t_cmd;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

int		ft_isspace(char c);
t_token	*new_token(t_tkn_type type, char *value);
void	add_token_node(t_token **head, t_token **curr, t_token **token);
char	*to_q_content(const char **input, char q_type);
void	to_variable(const char **input, t_token **head, t_token **curr);
t_token	*to_tokenize(const char *input);

void	dup_env_variables(t_utils *data, char **env);
void	manage_error(char *msg);

#endif