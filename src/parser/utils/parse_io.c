/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:20:44 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/28 02:22:17 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	is_redir_token(t_tok_kind type)
{
	return (type == T_GREAT || type == T_LESS ||
		type == T_DGREAT || type == T_DLESS);
}

t_io	*create_io_node(t_io_type type, int fd, char *file)
{
	t_io	*node;

	node = malloc(sizeof(t_io));
	if (!node)
		panic("malloc");
	node->type = type;
	node->fd = fd;
	node->file = ft_strdup(file);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	append_io(t_io **root, t_io *node)
{
	t_io	*tail;

	if (!root || !node)
		return ;
	if (!*root)
	{
		*root = node;
		return ;
	}
	tail = *root;
	while (tail->next)
		tail = tail->next;
	node->prev = tail;
	tail->next = node;
}

static t_io_type	get_io_type(t_token *prev_token)
{
	if (prev_token->kind == T_LESS)
		return (IO_IN);
	else if (prev_token->kind == T_GREAT)
		return (IO_OUT);
	else if (prev_token->kind == T_DLESS)
		return (IO_HEREDOC);
	else
		return (IO_APPEND);
}

t_io	*parse_io(t_token **token)
{
	t_io	*io;

	io = NULL;
	while (*token && is_redir_token((*token)->kind))
	{
		*token = (*token)->next;
		if ((*token)->kind != T_WORD)
			panic("invalid syntax");
		append_io(&io, create_io_node(get_io_type((*token)->prev),
			-1, (*token)->value));
		*token = (*token)->next;
	}
	return (io);
}
