/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:29:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/17 03:56:04 by obenchkr         ###   ########.fr       */
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
	{
		g_shell->has_heredoc = true;
		return (REDIR_HEREDOC);
	}
}

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	i = 0;
	cmd = expand_arg(cmd);
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
	free(cmd);
	return (result);
}

int	append_cmd_redir(t_list **args, t_redir **redir)
{
	t_token	token;

	token = get_next_token();
	if (token.type == T_WORD)
	{
		ft_lstadd_back(args, ft_lstnew(token.value));
		return (1);
	}
	return (ft_append_redir(redir, token));
}

t_node	*parse_cmd(void)
{
	t_node		*node;
	t_list		*args;
	t_redir		*redir;

	if (peek() == T_PIPE || peek() == T_ERROR)
		return (syntax_error("|"), NULL);
	if (peek() == T_EOF)
		return (NULL);
	args = NULL;
	redir = NULL;
	node = create_node(N_CMD, NULL, NULL);
	while (peek() != T_PIPE && peek() != T_EOF)
	{
		if (append_cmd_redir(&args, &redir) == -1)
			return (free_tree(node), NULL);
	}
	node->redir = redir;
	node->cmd = create_cmd(get_executable(args->content), ft_lsttab(args));
	return (free_list(args), node);
}
