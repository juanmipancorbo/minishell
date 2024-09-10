/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/10 12:54:48 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

/* ************************************************************************** */
/*                                    DEFINES                                 */
/* ************************************************************************** */
# define MALLOC_E "Malloc error:"
# define ERROR "Error:"

/* ************************************************************************** */
/*                                OPCODE / STRUCTS                            */
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
/*                                  PARSING                                   */
/* ************************************************************************** */

int		ft_isspace(char c);
t_token	*new_token(t_tkn_type type, char *value);
void	add_token_node(t_token **head, t_token **curr, t_token **token);
char	*to_q_content(const char **input, char q_type);
void	to_variable(const char **input, t_token **head, t_token **curr);
t_token	*to_tokenize(const char *input);
char	*to_expand(const char *str);

/* ************************************************************************** */
/*                                  EXECUTER                                  */
/* ************************************************************************** */
void	dup_env_variables(t_utils *data, char **env);
void	manage_error(char *msg);
void	init_execution(t_cmd *command, t_utils *utils);

/* ************************************************************************** */
/*                                  FILE DESCRIPTORS                          */
/* ************************************************************************** */
void	add_fdnode_back(t_red **lst, t_red *new);
t_red	*create_fd_node(char *path, int fd);
void	set_file_descriptor(t_cmd *cmd, char *path, t_tkn_type type);
int		redlst_size(t_red *lst);
#endif