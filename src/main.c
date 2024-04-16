/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 05:14:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "env.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_shell		*g_shell;

int	main(int argc, char **argv, char **envp)
{
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
			ft_exit();
		if (is_empty(g_shell->input))
			continue ;
		g_shell->tree = parse_input();
		if (!g_shell->has_syntax_error)
			ft_exec_node(g_shell->tree, false);
	}
	return (EXIT_SUCCESS);
}
