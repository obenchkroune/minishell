/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:08:14 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/17 08:50:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*create_pipe(t_node *left, t_node *right)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		panic("malloc");
	pipe->left = left;
	pipe->right = right;
	pipe->type = N_PIPE;
	return ((t_node *)pipe);
}

t_node	*create_exec(char *path, char **argv)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		panic("malloc");
	exec->type = N_EXEC;
	exec->path = path;
	exec->argv = argv;
	return ((t_node *)exec);
}

