/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/08 01:26:42 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(t_token token)
{
	g_shell->has_syntax_error = true;
	ft_fprintf(2, RED "minishell: " RESET
		"syntax error near unexpected token: `%s`\n",
		token.value);
}
