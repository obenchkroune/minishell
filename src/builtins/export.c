/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/23 22:50:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_name(char *name)
{
	if (!ft_isalpha(*name))
		return (false);
	while (*++name)
	{
		if (!ft_isalnum(*name))
			return (false);
	}
	return (true);
}

static void	export_error(char *key)
{
	ft_fprintf(2, "minishell: export: `%s' not a valid identifier\n",
		key);
	g_shell->last_exit_status = 1;
	free(key);
}

char	*get_export_key(const char *arg)
{
	char	*equal_sign;
	char	*key;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign || equal_sign - arg == 0)
		key = ft_strdup(arg);
	else
		key = ft_substr(arg, 0, equal_sign - arg);
	return (key);
}

static void	print_env(void)
{
	char	**envp;

	envp = g_shell->envp;
	while (envp && *envp)
	{
		printf("declare -x %s\n", *envp);
		envp++;
	}
}

void	ft_export(t_cmd *cmd)
{
	char	*key;
	int		i;

	if (cmd->argc == 1)
	{
		print_env();
		return ;
	}
	i = 1;
	while (i < cmd->argc)
	{
		key = get_export_key(cmd->argv[i]);
		if (is_valid_name(key))
		{
			set_env(key, ft_strchr(cmd->argv[i], '=') + 1);
			free(key);
			key = NULL;
		}
		else
			export_error(key);
		i++;
	}
}
