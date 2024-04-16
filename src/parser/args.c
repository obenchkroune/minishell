/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:17:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 07:27:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*create_arg_node(char *value, bool expand)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		panic("malloc");
	ft_bzero(arg, sizeof(t_arg));
	arg->content = value;
	arg->expand = expand;
	return (arg);
}

void	cleanup_arg_nodes(t_arg *args)
{
	if (!args)
		return ;
	cleanup_arg_nodes(args->next);
	free(args->content);
	free(args);
}

void	add_arg_node(t_arg **root, t_arg *arg)
{
	t_arg	*tail;

	if (!root || !arg)
		return ;
	if (*root == NULL)
	{
		*root = arg;
		return ;
	}
	tail = *root;
	while (tail->next)
		tail = tail->next;
	tail->next = arg;
}
