/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:39:23 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/10 14:24:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(char *path)
{
	ft_fprintf(2, "minishell: cd: %s: ", path);
	perror("");
	set_status(1);
}

void	cd_home(void)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
		panic_minishell("cd: HOME not set", 1);
	else
		cd_absolute(home);
}

void	cd_absolute(char *path)
{
	if (chdir(path) < 0)
		cd_error(path);
	else
		set_pwd(path);
}

void	cd_relative(char *path)
{
	char	*new_path;
	char	*temp;

	temp = ft_strjoin(get_env("PWD"), "/");
	new_path = ft_strjoin(temp, path);
	free(temp);
	if (chdir(path) < 0)
		cd_error(path);
	else
		set_pwd(new_path);
	free(new_path);
}

void	ft_cd(t_cmd *cmd)
{
	if (cmd->argc == 1)
		cd_home();
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		cd_absolute(get_env("OLDPWD"));
	else if (ft_strncmp(cmd->argv[1], "/", 1) == 0)
		cd_absolute(cmd->argv[1]);
	else
		cd_relative(cmd->argv[1]);
}
