/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/09 00:53:16 by yaharkat         ###   ########.fr       */
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

static void	g_shell_checks_update(void)
{
	char	**new_input;
	char	*tmp;

	g_shell->inside_unclosed_pipe = false;
	g_shell->tree = parse_input();
	if (!g_shell->has_heredoc && g_shell->has_unclosed_pipe)
	{
		new_input = ft_split(g_shell->input, '|');
		tmp = ft_strtrim(new_input[0], " ");
		add_history(tmp);
		set_history(tmp);
		free_matrix(new_input);
		free(tmp);
	}
	else if (!g_shell->has_heredoc)
	{
		add_history(g_shell->input);
		set_history(g_shell->input);
	}
	if (!g_shell->has_syntax_error)
		ft_exec_node(g_shell->tree, false);
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
		g_shell_checks_update();
	}
	return (EXIT_SUCCESS);
}
