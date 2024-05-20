/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/20 19:29:52 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	print_env(void)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void	process_argument(char *arg)
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
	if (*key != '\0')
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
