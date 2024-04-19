/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 10:38:39 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(char *msg)
{
	g_shell->lexer_idx = ft_strlen(g_shell->input) - 1;
	g_shell->has_syntax_error = true;
	g_shell->last_exit_status = 1;
	ft_fprintf(2, RED "minishell: " RESET "%s\n", msg);
}
