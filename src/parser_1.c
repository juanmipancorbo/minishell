/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:13:32 by jpancorb          #+#    #+#             */
/*   Updated: 2024/10/11 18:29:38 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_exe(char **env, char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

t_bool	fill_fd(t_cmd *cmd)
{
	t_red	*in_rd;
	t_red	*out_rd;

	in_rd = cmd->in_rd;
	out_rd = cmd->out_rd;
	while (out_rd)
	{
		if (!set_file_descriptor(out_rd))
			return (FALSE);
		out_rd = out_rd->next;
	}
	while (in_rd)
	{
		if (!set_file_descriptor(in_rd))
			return (FALSE);
		in_rd = in_rd->next;
	}
	return (TRUE);
}

static void	to_path_and_fd(t_cmd *cmds, t_utils *utils)
{
	t_cmd	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->args && curr->args[0] && !ft_isspace(*curr->args[0]))
		{
			curr->built_in = indentify_builtin(curr->args[0]);
			if (!curr->built_in)
			{
				curr->full_path = find_exe(utils->env_var, curr->args[0]);
				if (!curr->full_path)
					curr->full_path = ft_strdup(curr->args[0]);
				full_path_to_arg(curr);
			}
		}
		curr = curr->next;
	}
}

static t_bool	parse_tkn(t_token *token, t_cmd *cmd)
{
	if (token->type == WORD || token->type == VAR)
		add_arg(cmd, token->value);
	else if (token->type == RD_IN || token->type == RD_OUT
		|| token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next || token->next->type != WORD)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (FALSE);
		}
		token = token->next;
		add_red(cmd, token->value, token->prev->type);
	}
	return (TRUE);
}

t_cmd	*to_parse(t_token *tokens, t_utils *utils)
{
	t_cmd	*head;
	t_cmd	*curr;

	expand_tokens(tokens, utils->env_var);
	between_q(&tokens);
	head = create_cmd_node();
	if (!head)
		return (NULL);
	curr = head;
	while (tokens)
	{
		if (tokens->type == PIPE)
			curr = add_pipe(curr);
		else
		{
			if (!parse_tkn(tokens, curr))
				return (NULL);
			if (tokens->type == RD_IN || tokens->type == RD_OUT
				|| tokens->type == APPEND || tokens->type == HEREDOC)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	to_path_and_fd(head, utils);
	return (head);
}
