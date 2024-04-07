/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:39:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 05:19:39 by yaharkat         ###   ########.fr       */
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
	ft_bzero(redir, sizeof(t_redir));
	redir->fd = -1;
	redir->type = type;
	redir->file = file;
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

int	ft_append_redir(t_redir **root, t_token prev_token)
{
	t_token	token;
	t_redir	*tail;
	t_redir	*ret;

	if (peek() != T_WORD)
	{
		syntax_error(prev_token);
		return (-1);
	}
	token = get_next_token();
	ret = create_redir(get_redir_type(prev_token), token.value);
	if (*root == NULL)
	{
		*root = ret;
		return (0);
	}
	tail = *root;
	while (tail->next)
		tail = tail->next;
	tail->next = ret;
	return (0);
}

bool	is_empty(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}
