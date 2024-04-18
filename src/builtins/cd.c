/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:39:23 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/18 12:47:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_relative(char *path)
{
	char	*new_path;
	char	*temp;

	new_path = ft_strjoin(g_shell->cwd, "/");
	temp = ft_strjoin(new_path, path);
	free(new_path);
	new_path = temp;
	if (chdir(new_path) == -1)
		perror("minishell");
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
		perror("minishell");
		return ;
	}
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", path);
}

static void	cd_oldpwd(void)
{
	if (!get_env("OLDPWD"))
		panic_minishell("OLDPWD not set!", 1);
	else if (chdir(get_env("OLDPWD")) == -1)
		perror("minishell");
	else
	{
		set_env("OLDPWD", get_env("PWD"));
		set_env("PWD", get_env("OLDPWD"));
	}
}

static void	cd_home(void)
{
	if (!get_env("HOME"))
		panic_minishell("HOME not set!", 1);
	else if (chdir(get_env("HOME")) == -1)
		perror("minishell");
	else
	{
		set_env("OLDPWD", get_env("PWD"));
		set_env("PWD", get_env("HOME"));
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;

	path = cmd->argv[cmd->argc - 1];
	if (cmd->argc == 1)
		cd_home();
	else if (ft_strncmp(path, "-", 2) == 0)
		cd_oldpwd();
	else if (path[0] == '/')
		cd_absolute(path);
	else
		cd_relative(path);
	free(g_shell->cwd);
	g_shell->cwd = getcwd(NULL, 0);
}
