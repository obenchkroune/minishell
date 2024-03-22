/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:13:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 04:46:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(char *cmd)
{
	int		argc;
	char	*quote;
	char	*start;

	argc = 0;
	start = cmd;
	while (*cmd)
	{
		while (ft_isspace(*cmd))
			cmd++;
		if (ft_strchr("'\"", *cmd))
		{
			quote = ft_strchr(cmd + 1, *cmd);
			if (!quote)
				syntax_error("unclosed quote", start, cmd - start);
			cmd = quote + 1;
		}
		else
			while (*cmd && !ft_isspace(*cmd))
				cmd++;
		argc++;
		while (ft_isspace(*cmd))
			cmd++;
	}
	return (argc);
}

static char	*get_next_arg(char **cmd)
{
	char	*start;
	char	*quote;
	size_t	i;

	start = *cmd;
	while (*start && ft_isspace(*start))
		start++;
	*cmd = start;
	if (ft_strchr("'\"", *start))
	{
		quote = ft_strchr(start + 1, *start);
		*cmd = quote + 1;
		return (ft_substr(start, 1, quote - start - 1));
	}
	i = 0;
	while (start[i] && !ft_isspace(start[i]))
		i++;
	*cmd += i;
	return (ft_substr(start, 0, i));
}

static char	**parse_argv(char *cmd)
{
	char	**argv;
	int		i;
	int		argc;

	i = 0;
	argc = get_argc(cmd);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		panic("malloc");
	while (i < argc)
	{
		argv[i] = get_next_arg(&cmd);
		i++;
	}
	return (argv);
}

static t_cmd	*parse_cmd(t_token *token)
{
	char	*path;
	char	**argv;

	path = NULL; // TODO: parse the executable path
	argv = parse_argv(token->value);
	return (create_cmd(path, argv));
}

t_node	*create_cmd_node(t_lexer *lexer)
{
	t_token	*token;
	t_node	*node;
	t_io	*io;

	io = NULL;
	append_io(&io, parse_io(lexer));
	token = get_next_token(lexer);
	if (!token || token->type != T_CMD)
		syntax_error("unexpected syntax", token->value, token->idx);
	node = create_node(N_CMD, parse_cmd(token), NULL);
	free(token);
	append_io(&io, parse_io(lexer));
	node->io = io;
	return (node);
}
