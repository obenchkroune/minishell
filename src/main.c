/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/04 18:14:03 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	init_shell(argv, envp);
	signal_init();
	while (true)
	{
		cleanup_rotation();
		display_prompt();
		parse_input();
		if (g_shell->tree)
			ft_exec_node(g_shell->tree, false);
		close(g_shell->secondary_input);
	}
	cleanup_shell();
	return (EXIT_SUCCESS);
}
