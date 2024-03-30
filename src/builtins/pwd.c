/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:26:54 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:34:27 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_current_working_directory(void)
{
	char	*buffer;

	buffer = NULL;
	return (getcwd(buffer, 0));
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = get_current_working_directory();
	if (cwd)
		ft_fprintf(STDOUT_FILENO, "%s\n", cwd);
	else
		panic("pwd");
	free(cwd);
}
