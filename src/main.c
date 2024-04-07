/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 05:08:47 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*g_shell;

static char	*get_display_line(void)
{
	char		*line;
	static char	*display_line = NULL;

	free(display_line);
	line = ft_strjoin(GREEN "minishell@42:" RESET, g_shell->cwd);
	display_line = ft_strjoin(line, "$ ");
	free(line);
	return (display_line);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc, (void)argv;
	init_shell(envp);
	signal_init();
	while (true)
	{
		g_shell->prompt = get_display_line();
		g_shell->input = readline(g_shell->prompt);
		if (!g_shell->input)
			break ;
		if (is_empty(g_shell->input))
			continue ;
		g_shell->tree = parse_input();
		if (!g_shell->has_heredoc)
			add_history(g_shell->input);
		if (!g_shell->has_syntax_error)
			ft_exec_node(g_shell->tree, false);
		cleanup_rotation();
	}
	cleanup_shell();
	return (EXIT_SUCCESS);
}
