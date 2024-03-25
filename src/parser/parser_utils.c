/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:39:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 22:30:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_node	*create_cmd_node(t_cmd *cmd)
{
	t_node	*node;

	node = create_node(N_CMD, NULL, NULL);
	node->cmd = cmd;
	return (node);
}

size_t	get_argc(t_token *token)
{
	size_t	argc;

	argc = 0;
	while (token && token->kind == T_WORD)
	{
		token = token->next;
		argc++;
	}
	return (argc);
}

char	**parse_argv(t_token **token)
{
	size_t	argc;
	size_t	i;
	char	**argv;

	argc = get_argc(*token);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		panic("malloc");
	i = 0;
	while (i < argc)
	{
		argv[i++] = ft_strdup((*token)->value);
		*token = (*token)->next;
	}
	return (argv);
}
