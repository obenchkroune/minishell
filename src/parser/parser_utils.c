/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:39:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 00:25:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		panic("malloc");
	ft_bzero(node, sizeof(t_node));
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		panic("malloc");
	redir->type = type;
	redir->file = file;
	redir->fd = get_redir_fd(redir);
	redir->next = NULL;
	return (redir);
}

t_cmd	*create_cmd(char *path, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		panic("malloc");
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->path = path;
	cmd->argv = argv;
	cmd->argc = ft_tabsize(argv);
	return (cmd);
}

char	**ft_lsttab(t_list *list)
{
	char	**ret;
	size_t	len;
	size_t	i;

	len = ft_lstsize(list) + 1;
	ret = ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		panic("malloc");
	i = 0;
	while (list)
	{
		ret[i++] = list->content;
		list = list->next;
	}
	return (ret);
}

void	ft_append_redir(t_redir **root)
{
	t_token	token;
	t_redir	*tail;
	t_redir	*ret;

	token = get_next_token();
	if (peek() != T_WORD)
	{
		syntax_error(NULL);
		return ;
	}
	ret = create_redir(get_redir_type(token), get_next_token().value);
	if (*root == NULL)
	{
		*root = ret;
		return ;
	}
	tail = *root;
	while (tail->next)
		tail = tail->next;
	tail->next = ret;
}
