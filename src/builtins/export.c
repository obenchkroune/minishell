/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/22 22:17:19 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_error(char *key)
{
	ft_fprintf(2, "minishell: export: `%s' not a valid identifier\n", key);
	set_status(1);
}

char	*get_export_key(const char *arg)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (ft_itoa(arg[0] - '0'));
	while (arg && arg[i] && (ft_isalpha(arg[i]) || arg[i] == '_'))
	{
		i++;
	}
	return (ft_substr(arg, 0, i));
}

static bool	is_valid_export_key(const char *key)
{
	if (ft_strlen(key) == 0)
		return (false);
	while (key && *key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

static void	process_argument(char *arg)
{
	char	*key;
	char	*value;
	bool	append;

	append = false;
	key = get_export_key(arg);
	value = arg + ft_strlen(key);
	if (*value == '+')
	{
		append = true;
		value++;
	}
	if (*value == '=')
		value++;
	if (is_valid_export_key(key))
	{
		if (append)
			append_env(key, value);
		else
			set_env(key, value);
	}
	else
		export_error(arg);
	free(key);
}

void	ft_export(t_cmd *cmd)
{
	int		i;

	if (cmd->argc == 1)
	{
		print_env();
		return ;
	}
	i = 1;
	while (i < cmd->argc)
	{
		process_argument(cmd->argv[i]);
		i++;
	}
}
