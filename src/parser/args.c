/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:17:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 10:16:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*create_arg_node(char *value, t_arg_type type)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		panic("malloc");
	ft_bzero(arg, sizeof(t_arg));
	arg->content = value;
	arg->type = type;
	return (arg);
}

void	cleanup_arg_nodes(t_arg *args)
{
	t_arg	*temp;

	while (args)
	{
		temp = args->next;
		free(args->content);
		free(args);
		args = temp;
	}
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
