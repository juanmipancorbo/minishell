/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:13:32 by jpancorb          #+#    #+#             */
/*   Updated: 2024/11/12 17:51:55 by jpancorb         ###   ########.fr       */
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
				if (!curr->full_path && !ft_strncmp(curr->args[0], "./", 2))
					curr->full_path = ft_strdup(curr->args[0]);
				full_path_to_arg(curr);
			}
		}
		if (check_env_name("_", utils, 1))
			replace_env_var("_", to_last_argument(curr), utils->env_var);
		curr = curr->next;
	}
}

static t_bool	parse_tkn(t_token *token, t_cmd *cmd)
{
	if (token->type == UNMATCHED)
		cmd->args = NULL;
	if (token->type == VAR)
	{
		if (cmd->args && ft_strncmp(cmd->args[0], "echo", 5) == 0)
			add_arg(cmd, ft_strdup(token->value));
		else
			expand_and_add_arg(cmd, token->value);
	}
	else if (token->type == WORD || token->type == SINGLE_Q)
		add_arg(cmd, ft_strdup(token->value));
	else if (token->type >= 2 && token->type <= 5)
	{
		if (!token->next || token->next->type != WORD)
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			g_exit_code = 2;
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

	expand_tokens(tokens, utils);
	head = create_cmd_node();
	if (!head)
		return (NULL);
	curr = head;
	while (tokens)
	{
		if (tokens->type == WORD && ft_strchr(tokens->value, '='))
			tokens->value = process_token_value(tokens->value, utils);
		if (tokens->type == PIPE)
			curr = add_pipe(curr);
		else
		{
			if (!parse_tkn(tokens, curr))
				return (NULL);
			if (tokens->type >= 2 && tokens->type <= 5)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	to_path_and_fd(head, utils);
	return (head);
}
