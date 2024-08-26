/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:04:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/26 22:00:23 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	SINGLE_QT,
	DOUBLE_QT,
	VAR,
	EXIT_STATUS,
}							t_tkn_type;

typedef struct s_token
{
	t_tkn_type		type;
	char			*value;
	struct s_token	*next;
}							t_token;

typedef struct s_cmd
{
	char			**args;
	char			*in_rd;
	char			*out_rd;
	int				append;
	struct s_cmd	*next;
}							t_cmd;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

int	ft_isspace(char *s);

#endif