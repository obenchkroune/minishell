/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 04:45:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "env.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_shell		*g_shell;

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
	g_shell->should_continue_execution = true;
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
		g_shell->lexer_idx = 0;
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
