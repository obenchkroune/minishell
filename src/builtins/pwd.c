/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:26:54 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 04:56:18 by obenchkr         ###   ########.fr       */
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
	ft_fprintf(STDOUT_FILENO, "%s\n", g_shell->cwd);
}
