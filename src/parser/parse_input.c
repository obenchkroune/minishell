/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:30:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 16:59:51 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_input(void)
{
	if (is_empty(g_shell->input))
	{
		g_shell->tree = NULL;
		return ;
	}
	g_shell->tree = parse_pipe();
	if (!g_shell->has_heredoc)
		add_history(g_shell->input);
}
