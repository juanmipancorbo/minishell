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
# include <signal.h>
# include <sys/stat.h>

extern int	g_exit_code;

/* ************************************************************************** */
/*                                    DEFINES                                 */
/* ************************************************************************** */
# define MALLOC_E "Malloc error\n"
# define DUP_E "Dup error\n"
# define FORK_E "Fork error\n"
# define PIPE_E "Pipe error\n"
# define EXEC_E "Exec error\n"
# define WRITE_END 1
# define READ_END 0
# define HEREDOC_F "./heredoc_tmp"
# define VALUE_BUFFER 1024

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
	SINGLE_Q = 8,
	UNMATCHED = 9,
	QUOTED = 10,
}							t_tkn_type;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_token
{
	t_tkn_type		type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}							t_token;

typedef struct s_expand_data
{
	size_t	i;
	size_t	j;
	int		in_single_quote;
	int		in_double_quote;
}							t_expand_data;

typedef struct s_utils
{
	char	**env_var;
	pid_t	*process_id;
	char	**export_var;
	char	*pid;
	t_bool	is_pipe;
}							t_utils;

typedef struct s_red
{
	char			*file;
	int				type;
	int				quoted;
	int				fd;
	char			*herecoc_f;
	struct s_red	*next;
}							t_red;

typedef struct s_cmd
{
	char			**args;
	char			*full_path;
	t_red			*in_rd;
	t_red			*out_rd;
	int				(*built_in)(struct s_cmd *, t_utils *);
	struct s_cmd	*next;
	struct s_cmd	*prev;
}							t_cmd;

/* ************************************************************************** */
/*                                  TOKENIZER                                 */
/* ************************************************************************** */
void	add_token_node(t_token **head, t_token **curr, t_token **token);
void	free_env_copy(t_utils *utils);
t_token	*new_token(t_tkn_type type, char *value);
void	q_content(const char *start, const char *input, t_token **head,
			t_token **curr);
char	*single_q(const char **input, char q_type);
void	double_q(const char **input, t_token **head, t_token **curr);
void	to_quotes_unmatched(t_token **head, t_token **curr);
void	to_variable(const char **input, t_token **head, t_token **curr);
t_token	*to_tokenize(const char *input);
char	*process_token_value(char *value, t_utils *utils);
void	to_get_pid(t_utils *utils);
void	parse_pid(t_utils *utils, char *buffer);
void	analyze_symbol(const char **input);

/* ************************************************************************** */
/*                                   PARSER                                   */
/* ************************************************************************** */
t_cmd	*to_parse(t_token *tokens, t_utils *utils);
t_cmd	*add_pipe(t_cmd *curr);
void	add_arg(t_cmd *cmd, char *arg);
t_red	*create_red_node(char *file, int type);
void	add_red(t_cmd *cmd, char *file, int type);
void	add_in_red(t_cmd *cmd, t_red *red);
void	add_out_red(t_cmd *cmd, t_red *red);
t_cmd	*create_cmd_node(void);
char	*expand_var(char *var, char **env);
void	expand_tokens(t_token *tokens, t_utils *utils);
void	expand_and_add_arg(t_cmd *cmd, char *expansion);
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
char	*copy_after_str(const char *src, const char *target);
char	*replace_str(char *old_str, char *new_str);
void	to_free_four(char *a, char *b, char *c, char *d);
char	*ft_strjoin_free(char *s1, char const *s2);
char	*ft_itoa(int nb);

/* ************************************************************************** */
/*                                  EXECUTER                                  */
/* ************************************************************************** */
void	dup_env_variables(t_utils *utils, int pid, char **from, char ***to);
int		to_env_list_size(char **env_list);
void	to_no_env(t_utils *utils);
void	init_execution(t_cmd **command, t_utils *utils);
int		**create_pipes_fd(int np);
pid_t	*get_pid_array(int nbs_process);
void	check_cmd_access(t_cmd *cmd);

/* ************************************************************************** */
/*                               FILE DESCRIPTORS                             */
/* ************************************************************************** */
void	add_fdnode_back(t_red **lst, t_red *new);
t_bool	set_file_descriptor(t_red *red);
t_bool	check_files(char *path);
t_bool	fill_fd(t_cmd *cmd);
t_bool	heredoc_complete(t_cmd *cmd, t_utils *utils);
char	*new_heredoc_filename(void);
void	expand_hd_word(char *line, t_utils *utils, int fd);

/* ************************************************************************** */
/*                                EXIT & ERRORS     	                      */
/* ************************************************************************** */
void	dir_error(char *msg, int exit_code);
void	file_error(char *msg, int exit_code);
void	delete_herdocf(char *heredocf);
void	exit_error(char *msg, int exit_code);
void	cmd_error(char *str, int exit_code);
void	heredoc_error(char *delimiter);


/* ************************************************************************** */
/*                                 LIST UTILS		                          */
/* ************************************************************************** */
int		cmd_lst_size(t_cmd **cmd);
t_red	*red_last_node(t_red *lst);
int		redlst_size(t_red *lst);
t_red	*create_fd_node(char *path, int fd);
void	close_fd_redlst(t_cmd *cmd);

/* ************************************************************************** */
/*                               PIPES FUNCTIONS		                      */
/* ************************************************************************** */
void	set_pipes_fd(t_cmd *cmd, int cmd_id, int **pipes_fd, pid_t pid);

/* ************************************************************************** */
/*                                  BUILT IN			                      */
/* ************************************************************************** */
int		(*indentify_builtin(char *str))(t_cmd *cmd, t_utils *utils);
int		ft_cd(t_cmd *cmd, t_utils *utils);
int		ft_echo(t_cmd *cmd, t_utils *utils);
int		ft_env(t_cmd *cmd, t_utils *utils);
int		ft_export(t_cmd *cmd, t_utils *utils);
int		ft_pwd(t_cmd *cmd, t_utils *utils);
int		ft_unset(t_cmd *cmd, t_utils *utils);
int		ft_exit(t_cmd *cmd, t_utils *utils);

/* ************************************************************************** */
/*                                BUILT IN UTILS			                  */
/* ************************************************************************** */
t_bool	is_forked(t_cmd *cmd);
int		replace_env_var(char *var_name, char *new_value, char **env);
void	add_env_var(char *var_name, char *value, char ***env);
char	*expand_dollars(const char *value, t_utils *utils);
int		check_env_name(char *var_name, t_utils *utils, int env);
void	to_no_env(t_utils *utils);
void	update_shlvl(t_utils *utils);
char	*to_last_argument(t_cmd *cmd);

/* ************************************************************************** */
/*                                  SIGNALS			                          */
/* ************************************************************************** */

void	init_signals(int i);
void	wait_process(t_utils *utils, int nb_process);

#endif
