/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 17:12:55 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*g_shell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc, (void)argv;
	init_shell(envp);
	signal_init();
	while (true)
	{
		cleanup_rotation();
		display_prompt();
		parse_input();
		// if (g_shell->tree)
		// 	printf("tree cmd: %p\n", g_shell->tree->cmd);
		ft_exec_node(g_shell->tree, false);
	}
	return (EXIT_SUCCESS);
}
