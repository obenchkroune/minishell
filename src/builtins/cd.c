/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:39:23 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/01 20:02:49 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_error(char *path)
{
	ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
	g_shell->last_exit_status = 1;
}
static void	cd_back(void)
{
	char	*temp;

	if (chdir("..") == -1)
	{
		cd_error(get_env("PWD"));
		return ;
	}
	temp = getcwd(NULL, 0);
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", temp);
	free(temp);
}

static void	cd_relative(char *path)
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

static void	cd_absolute(char *path)
{
	if (chdir(path) == -1)
	{
		cd_error(path);
		return ;
	}
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", path);
}

static void	cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env("OLDPWD");
	if (!oldpwd)
	{
		panic_minishell("cd: OLDPWD not set!", 1);
		return ;
	}
	cd_absolute(oldpwd);
}

static void	cd_home(void)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
	{
		panic_minishell("cd: HOME not set!", 1);
		return ;
	}
	cd_absolute(home);
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	*cwd;

	if (cmd->argc > 2)
	{
		panic_minishell("cd: too many arguments", 1);
		return ;
	}
	path = cmd->argv[1];
	if (cmd->argc == 1)
		cd_home();
	else if (ft_strncmp(path, "-", 2) == 0)
		cd_oldpwd();
	else if (path[0] == '/')
		cd_absolute(path);
	else if (ft_strncmp(path, "..", 3) == 0)
		cd_back();
	else
		cd_relative(path);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		free(g_shell->cwd);
		g_shell->cwd = cwd;
	}
}
