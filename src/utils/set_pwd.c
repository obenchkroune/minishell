/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 14:25:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd(char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd: cannot access parent directories");
		if (!path)
		{
			free(cwd);
			return ;
		}
		cwd = ft_strdup(path);
		if (!cwd)
			panic("malloc");
	}
	set_env("OLDPWD", g_shell->cwd);
	free(g_shell->cwd);
	g_shell->cwd = cwd;
	set_env("PWD", g_shell->cwd);
}
