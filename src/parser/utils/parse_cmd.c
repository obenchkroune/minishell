/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:52:42 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/30 03:14:31 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		argv[i++] = ft_expand((*token)->value);
		*token = (*token)->next;
	}
	return (argv);
}

static t_cmd	*parse_cmd_props(t_token **token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		panic("malloc");
	cmd->argv = parse_argv(token);
	cmd->path = get_executable(cmd->argv[0]);
	return (cmd);
}

t_node	*parse_cmd(t_token **token)
{
	t_node	*node;
	t_io	*io;

	io = parse_io(token);
	if (!*token || (*token)->kind != T_WORD)
		panic("invalid syntax!");
	node = create_node(N_CMD, NULL, NULL);
	node->cmd = parse_cmd_props(token);
	append_io(&io, parse_io(token));
	node->io = io;
	return (node);
}
