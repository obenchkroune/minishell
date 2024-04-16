/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:30:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 04:30:39 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_input(void)
{
	g_shell->has_syntax_error = false;
	g_shell->lexer_idx = 0;
	return (parse_pipe());
}
