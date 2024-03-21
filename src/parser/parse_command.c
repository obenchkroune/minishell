/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:09:05 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/21 03:49:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

static int	get_argc(char *cmd)
{
	int		argc;
	char	*pair_quote;

	argc = 0;
	while (*cmd)
	{
		skip_whitespace(&cmd);
		if (!*cmd || !ft_isprint(*cmd))
			break ;
		argc++;
		if (ft_strchr("'\"", *cmd))
		{
			pair_quote = ft_strchr(cmd + 1, *cmd);
			if (!pair_quote)
				panic("Syntax error: unclosed quote");
			cmd = pair_quote + 1;
		}
		else
		{
			while (!ft_strchr(WHITESPACE, *cmd))
				cmd++;
		}
	}
	return (argc);
}

static char	*get_next_arg(char **s)
{
	char	*cmd;
	char	*start;
	char	*arg;

	cmd = *s;
	skip_whitespace(&cmd);
	start = cmd;
	if (ft_strchr("\"'", *cmd))
	{
		cmd = ft_strchr(cmd + 1, *cmd) + 1;
		arg = ft_substr(start, 1, cmd - start - 2);
	}
	else
	{
		while (!ft_strchr(WHITESPACE, *cmd))
			cmd++;
		arg = ft_substr(start, 0, cmd - start);
	}
	*s = cmd;
	return (arg);
}

static char	**parse_argv(char *cmd)
{
	char	**argv;
	int		argc;
	int		i;

	argc = get_argc(cmd);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		panic("malloc");
	i = 0;
	while (i < argc)
	{
		argv[i] = get_next_arg(&cmd);
		i++;
	}
	return (argv);
}

t_node	*parse_command(t_token **token)
{
	t_cmd	*node;

	if (!token || !*token || (*token)->type != T_COMMAND)
		panic("Invalid Syntax");
	node = (t_cmd *)create_command(NULL, NULL);
	node->argv = parse_argv((*token)->value);
	*token = (*token)->next;
	// TODO: get the executable path from the env vars
	return ((t_node *)node);
}

