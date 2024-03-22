#include "minishell.h"

int	get_argc(char *cmd)
{
	int		argc;
	char	*quote;

	argc = 0;
	while (*cmd)
	{
		while (ft_isspace(*cmd))
			cmd++;
		if (ft_strchr("'\"", *cmd))
		{
			quote = ft_strchr(cmd + 1, *cmd);
			if (!quote)
				panic("syntax error: unclosed quote");
			cmd = quote + 1;
		}
		else
		{
			while (*cmd && !ft_isspace(*cmd))
				cmd++;
		}
		argc++;
		while (ft_isspace(*cmd))
			cmd++;
	}
	return (argc);
}

char	*get_next_arg(char **cmd)
{
	char	*start;
	char	*quote;
	size_t	i;

	start = *cmd;
	i = 0;
	while (*start && ft_isspace(*start))
		start++;
	if (ft_strchr("'\"", *start))
	{
		quote = ft_strchr(start + 1, *start);
		if (!quote)
			panic("syntax error: unclosed quote");
		*cmd = quote + 1;
		return (ft_substr(start, 1, start - *cmd - 1));
	}
	while (start[i] && !ft_isspace(start[i]))
		i++;
	*cmd += i;
	return (ft_substr(start, 0, i));
}

char	**parse_argv(char *cmd)
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

t_cmd	*parse_cmd(t_token *token)
{
	char	*path;
	char	**argv;

	if (token->type != T_CMD)
		panic("invalid syntax");
	path = NULL; // TODO: parse the executable path
	argv = parse_argv(token->value);
	return (create_cmd(path, argv));
}
