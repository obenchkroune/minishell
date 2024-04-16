/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 04:57:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(char *s)
{
	g_shell->has_syntax_error = true;
	ft_fprintf(2, RED "minishell: " RESET
		"syntax error near unexpected token: `%s`\n", s);
}
