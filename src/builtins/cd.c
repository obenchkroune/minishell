/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:39:23 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/06 05:15:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_dir_to_path(char *path)
{
	char	*pwd;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	if (!pwd)
	{
		ft_fprintf(STDERR_FILENO, "cd: error retrieving current directory: ");
		perror("getcwd");
		return ;
	}
	set_env("OLDPWD", pwd);
	if (chdir(path) != 0)
	{
		panic_minishell(strerror(errno), 1);
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
	char	*home_env;

	home_env = get_env("HOME");
	if (!home_env)
	{
		ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		return ;
	}
	path = ft_strdup(home_env);
	if (path == NULL)
	{
		panic_minishell(NO_HOME, 1);
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
		free(g_shell->cwd);
		g_shell->cwd = getcwd(NULL, 0);
		return ;
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		if (!get_env("OLDPWD"))
		{
			panic_minishell(NO_OLDPWD, 1);
			return ;
		}
		current_path = ft_strdup(get_env("OLDPWD"));
		if (current_path == NULL)
			return ;
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_path(current_path);
	}
	free(g_shell->cwd);
	free(current_path);
	g_shell->cwd = getcwd(NULL, 0);
}
