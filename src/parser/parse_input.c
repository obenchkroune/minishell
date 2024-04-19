/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:30:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 10:37:34 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_input(void)
{
	g_shell->tree = parse_pipe();
	if (!g_shell->has_heredoc)
		add_history(g_shell->input);
	if (g_shell->has_syntax_error)
	{
		free_tree(g_shell->tree);
		g_shell->tree = NULL;
		return (-1);
	}
	return (0);
}
