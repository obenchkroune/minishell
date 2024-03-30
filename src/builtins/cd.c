/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:39:23 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:37:52 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_dir_to_path(char *path)
{
	char	*pwd;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	set_env("OLDPWD", pwd);
	if (chdir(path) != 0)
	{
		panic("cd");
		return ;
	}
	pwd = getcwd(buffer, 2048);
	set_env("PWD", pwd);
}

static void	change_dir_to_oldpwd(char *path)
{
	ft_fprintf(STDOUT_FILENO, "%s\n", path);
	change_dir_to_path(path);
}

static void	change_dir_to_home(void)
{
	char	*path;

	path = ft_strdup(get_env("HOME")->value);
	if (path == NULL)
	{
		panic(NO_HOME);
		free(path);
		return ;
	}
	change_dir_to_path(path);
	free(path);
}

void	ft_cd(char **args)
{
	char	*current_path;
	char	*path;

	path = args[1];
	if ((!path) || ft_strncmp(path, "~", ft_strlen(path)) == 0)
	{
		change_dir_to_home();
		return ;
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		current_path = ft_strdup(get_env("OLDPWD")->value);
		if (current_path == NULL)
		{
			panic(NO_OLDPWD);
			return ;
		}
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_path(current_path);
	}
	free(current_path);
}
