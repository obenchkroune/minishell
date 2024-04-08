/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/08 02:03:40 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*g_shell;

static char	*get_display_line(void)
{
	char	*line;
	char	*display_line;

	line = ft_strjoin(GREEN "minishell@42:" RESET, g_shell->cwd);
	display_line = ft_strjoin(line, "$ ");
	free(line);
	return (display_line);
}

static bool	is_invalid_pipe(char *input)
{
	int		count;
	char	*pipe_p;

	pipe_p = ft_strrchr(g_shell->input, '|');
	if (!pipe_p)
		return (false);
	if (ft_strnstr(input, "|||", ft_strlen(input)))
		return (true);
	count = 0;
	while (*input)
	{
		if (*input == '|')
			count++;
		input++;
	}
	return (count > 2 && is_empty(pipe_p + 1));
}
static int	handle_unclosed_pipe(void)
{
	char	*input_pipe_unclosed;
	char	*tmp;
	int		status;

	g_shell->inside_unclosed_pipe = true;
	if (is_invalid_pipe(g_shell->input))
		return (-2);
	if (ft_strrchr(g_shell->input, '|') && is_empty(ft_strrchr(g_shell->input,
				'|') + 1))
	{
		input_pipe_unclosed = readline(">");
		if (!input_pipe_unclosed)
			return (free(input_pipe_unclosed), -1);
		if (is_empty(input_pipe_unclosed))
		{
			status = handle_unclosed_pipe();
			if (status < 0)
				return (free(input_pipe_unclosed), status);
			return (free(input_pipe_unclosed), 0);
		}
		tmp = g_shell->input;
		g_shell->input = ft_strjoin(g_shell->input, input_pipe_unclosed);
		(free(input_pipe_unclosed), free(tmp));
		if (ft_strrchr(g_shell->input, '|') && is_empty(ft_strrchr(g_shell->input,
				'|') + 1))
			return (handle_unclosed_pipe());
	}
	return (0);
}

static void	exit_eof(int status)
{
	if (status == -1)
		panic_minishell("syntax error: unexpected end of file", 2);
	else if (status == -2)
		panic_minishell("syntax error: unexpected '|'", 2);
	cleanup_rotation();
	if (status != -2)
	{
		cleanup_shell();
		ft_fprintf(STDOUT_FILENO, "exit\n");
	}
	if (status != -2 && status < 0)
		exit(2);
	else if (status != -2)
		exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	int	check_status;
  
	(void)argc, (void)argv;
	init_shell(envp);
	signal_init();
	while (true)
	{
		cleanup_rotation();
		g_shell->prompt = get_display_line();
		g_shell->input = readline(g_shell->prompt);
		if (!g_shell->input)
			exit_eof(0);
		if (is_empty(g_shell->input))
			continue ;
		check_status = handle_unclosed_pipe();
		if (check_status < 0)
		{
			exit_eof(check_status);
			continue ;
		}
		g_shell->inside_unclosed_pipe = false;
		g_shell->tree = parse_input();
		if (!g_shell->has_heredoc)
			add_history(g_shell->input);
		if (!g_shell->has_syntax_error)
			ft_exec_node(g_shell->tree, false);
	}
	return (EXIT_SUCCESS);
}
