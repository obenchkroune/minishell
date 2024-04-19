/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:26:54 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 06:00:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	if (!g_shell->cwd)
		g_shell->cwd = ft_strdup(get_env("PWD"));
	ft_fprintf(STDOUT_FILENO, "%s\n", g_shell->cwd);
}
