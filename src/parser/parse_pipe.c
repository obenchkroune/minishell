/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 04:34:00 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir_type	get_redir_type(t_token token)
{
	t_token_type	type;

	type = token.type;
	if (type == T_APPEND)
		return (REDIR_APPEND);
	else if (type == T_REDIR_IN)
		return (REDIR_IN);
	else if (type == T_REDIR_OUT)
		return (REDIR_OUT);
	else
		return (REDIR_HEREDOC);
}

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	result = NULL;
	if (get_env("PATH") == NULL)
		return (NULL);
	path = ft_split(get_env("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		result = ft_strjoin(path[i], slash_cmd);
		if (access(result, F_OK) == 0)
			break ;
		free(result);
		result = NULL;
		i++;
	}
	free(slash_cmd);
	free_tab(path);
	return (result);
}

t_node	*parse_cmd(void)
{
	t_node		*node;
	t_token		token;
	t_list		*args;
	t_redir		*redir;

	if (peek() == T_PIPE)
	{
		syntax_error("syntax error near unexpected token '|'");
		return (NULL);
	}
	args = NULL;
	redir = NULL;
	node = create_node(N_CMD, NULL, NULL);
	while (peek() != T_PIPE && peek() != T_EOF)
	{
		token = get_next_token();
		if (token.type == T_WORD)
			ft_lstadd_back(&args, ft_lstnew(token.value));
		else
			ft_append_redir(&redir, token);
	}
	node->redir = redir;
	node->cmd = create_cmd(get_executable(args->content), ft_lsttab(args));
	return (node);
}

t_node	*parse_pipe(void)
{
	t_node	*node;

	node = parse_cmd();
	if (!node)
		return (node);
	if (peek() == T_PIPE)
	{
		get_next_token();
		node = create_node(N_PIPE, node, parse_pipe());
	}
	return (node);
}

t_node	*parse_input(void)
{
	g_shell->has_syntax_error = false;
	g_shell->lexer_idx = 0;
	return (parse_pipe());
}
