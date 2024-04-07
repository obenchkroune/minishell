/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:26:54 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/07 06:31:06 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	*get_current_working_directory(void)
// {
// 	char	*buffer;

// 	buffer = NULL;
// 	return (getcwd(buffer, 0));
// }

void	ft_pwd(void)
{
	if (!g_shell->cwd)
		g_shell->cwd = ft_strdup(get_env("PWD"));
	ft_fprintf(STDOUT_FILENO, "%s\n", g_shell->cwd);
}
