/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:29:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:38:16 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_node	*parse_subshell(void)
{
	t_node	*node;

	get_next_token();
	node = parse_cmd();
	while (peek() != T_CLOSE_PAREN && peek() != T_EOF)
		node = parse_meta(node);
	if (peek() != T_CLOSE_PAREN)
		return (syntax_error(NULL), node);
	get_next_token();
	return (create_node(N_SUBSHELL, node, NULL));
}

void	parse_args(t_list **args, t_redir **redir)
{
	*args = NULL;
	*redir = NULL;
	while (peek() == T_WORD || is_redir_token(peek()))
	{
		if (peek() == T_WORD)
			ft_lstadd_back(args, ft_lstnew(get_next_token().value));
		else
			ft_append_redir(redir);
	}
}

t_node	*parse_cmd(void)
{
	t_node	*node;
	t_list	*args;
	t_redir	*redir;

	if (peek() == T_EOF)
		return (NULL);
	if (peek() == T_OPEN_PAREN)
		return (parse_subshell());
	if (peek() != T_WORD && !is_redir_token(peek()))
		return (syntax_error(NULL), NULL);
	node = create_node(N_CMD, NULL, NULL);
	parse_args(&args, &redir);
	node->redir = redir;
	if (args)
	{
		expand_wildcard_args(args);
		node->cmd = create_cmd(NULL, ft_lsttab(args));
	}
	return (free_list(args), node);
}
