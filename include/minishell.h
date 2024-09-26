/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/09/18 20:15:25 by jpancorb         ###   ########.fr       */
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
# include <unistd.h>

/* ************************************************************************** */
/*                                    DEFINES                                 */
/* ************************************************************************** */
# define MALLOC_E "Malloc error"
# define ERROR "Error"
# define WRITE_END 1
# define READ_END 0
# define HEREDOC_F "./heredoc_tmp"

/* ************************************************************************** */
/*                                OPCODE / STRUCTS                            */
/* ************************************************************************** */
typedef enum e_tkn_type
{
	WORD = 0,
	PIPE = 1,
	RD_IN = 2,
	RD_OUT = 3,
	APPEND = 4,
	HEREDOC = 5,
	DOUBLE_Q = 6,
	VAR = 7,
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
	char			*file;
	int				type;
	int				fd;
	struct s_red	*next;
}							t_red;

typedef struct s_cmd
{
	char			**args;
	char			*full_path;
	t_red			*in_rd;
	t_red			*out_rd;
	int 			(*built_in)(struct s_cmd *, t_utils *);
	struct s_cmd	*next;
	struct s_cmd	*prev;
}							t_cmd;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

/* ************************************************************************** */
/*                                  TOKENIZER                                 */
/* ************************************************************************** */
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
/*                                   PARSER                                   */
/* ************************************************************************** */
t_cmd	*to_parse(t_token *tokens, char **env);
t_cmd	*add_pipe(t_cmd *curr);
void	add_arg(t_cmd *cmd, char *arg);
t_red	*create_red_node(char *file, int type);
void	add_red(t_cmd *cmd, char *file, int type);
void	add_in_red(t_cmd *cmd, t_red *red);
void	add_out_red(t_cmd *cmd, t_red *red);
t_cmd	*create_cmd_node(void);
char	*expand_var(char *var, char **env);
void	expand_tokens(t_token *tokens, char **env);
void	between_q(t_token **tokens);
char	*join_path_cmd(char *path, char *cmd);
char	*get_env_value(char **env, const char *var_name);
void	ft_free_split(char **split);
void	print_cmds(t_cmd *cmds);
void	free_cmds(t_cmd *cmds);
void	free_q(t_token **curr, t_token **end);
void	full_path_to_arg(t_cmd	*cmd);

//* TEST FUNCTIONS *//
void	print_tokens(t_token *tokens);
void	print_var(char **env);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
int		ft_isspace(char c);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcpy(char *dst, const char *src);

/* ************************************************************************** */
/*                                  EXECUTER                                  */
/* ************************************************************************** */
void	dup_env_variables(t_utils *data, char **env);
void	init_execution(t_cmd **command, t_utils *utils);
int		**create_pipes_fd(int np);

/* ************************************************************************** */
/*                               FILE DESCRIPTORS                             */
/* ************************************************************************** */
void	add_fdnode_back(t_red **lst, t_red *new);
void	set_file_descriptor(t_cmd *cmd, char *path, t_tkn_type type);
void	read_loop(char *str);
t_bool	check_files(char *path);

/* ************************************************************************** */
/*                                  EXIT & ERRORS     	                      */
/* ************************************************************************** */
void	clean_exit(t_cmd **cmd);
void	manage_error(char *msg);

/* ************************************************************************** */
/*                                  LIST UTILS		                          */
/* ************************************************************************** */
int		cmd_lst_size(t_cmd **cmd);
t_red	*red_last_node(t_red *lst);
int		redlst_size(t_red *lst);
t_red	*create_fd_node(char *path, int fd);
void	close_fd_redlst(t_cmd *cmd);

/* ************************************************************************** */
/*                                  PIPES FUNCTIONS		                      */
/* ************************************************************************** */
void	set_pipes_fd(t_cmd *cmd, int cmd_id, int **pipes_fd, pid_t pid);

/* ************************************************************************** */
/*                                  BUILT IN			                      */
/* ************************************************************************** */
int (*indetyfy_buitin(char *str))(t_cmd *, t_utils *);
int ft_cd(t_cmd *cmd, t_utils *utils);
int ft_echo(t_cmd *cmd, t_utils *utils);
int ft_env(t_cmd *cmd, t_utils *utils);
int ft_export(t_cmd *cmd, t_utils *utils);
int ft_pwd(t_cmd *cmd, t_utils *utils);
int ft_unset(t_cmd *cmd, t_utils *utils);
int ft_exit(t_cmd *cmd, t_utils *utils);
#endif
