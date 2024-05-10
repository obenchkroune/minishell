/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:28:07 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 12:26:05 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(char *path)
{
	ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
	set_status(1);
}

void	cd_relative(char *path)
{
	char	*new_path;
	char	*temp;

	new_path = ft_strjoin(g_shell->cwd, "/");
	temp = ft_strjoin(new_path, path);
	free(new_path);
	new_path = temp;
	if (chdir(new_path) == -1)
		cd_error(path);
	else
	{
		set_env("OLDPWD", get_env("PWD"));
		set_env("PWD", new_path);
	}
	free(new_path);
}

void	cd_absolute(char *path)
{
	if (chdir(path) == -1)
	{
		cd_error(path);
		return ;
	}
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", path);
}
