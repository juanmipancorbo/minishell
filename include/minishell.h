/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/11 20:44:05 by jpancorb         ###   ########.fr       */
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
# define MALLOC_E "Malloc error"
# define ERROR "Error"
# define READ_END 0
# define WRITE_END 1


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
char	*ft_strndup(const char *s, size_t n);
void	add_token_node(t_token **head, t_token **curr, t_token **token);
void	free_env_copy(char **env_var);
t_token	*new_token(t_tkn_type type, char *value);
void	q_content(const char *start, const char *input, t_token **head,
			t_token **curr);
char	*single_q(const char **input, char q_type);
void	double_q(const char **input, t_token **head, t_token **curr);
void	to_variable(const char **input, t_token **head, t_token **curr);
t_token	*to_tokenize(const char *input);

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