/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:40:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 14:25:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_env **root, char *key, char *value)
{
	t_env	*tail;
	t_env	*env;

	if (!root || !key || !value)
		return ;
	env = env_constructor(key, value);
	if (!*root)
	{
		*root = env;
		return ;
	}
	tail = *root;
	while (tail->next)
	{
		tail = tail->next;
	}
	tail->next = env;
}

t_env	*env_constructor(const char *key, const char *value)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		panic("malloc");
	result->key = ft_strdup(key);
	result->value = ft_strdup(value);
	result->next = NULL;
	return (result);
}

size_t	env_list_size(void)
{
	size_t	size;
	t_env	*env;

	env = g_shell->env;
	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

char	*join_env(char *name, char *value)
{
	size_t	buf_size;
	char	*result;

	buf_size = ft_strlen(name) + ft_strlen(value) + 2;
	result = malloc(sizeof(char) * buf_size);
	if (!result)
		panic("malloc");
	result[0] = '\0';
	ft_strlcat(result, name, buf_size);
	ft_strlcat(result, "=", buf_size);
	ft_strlcat(result, value, buf_size);
	return (result);
}

void	update_envp(void)
{
	t_env	*env;
	char	**envp;
	size_t	size;
	size_t	i;

	env = g_shell->env;
	size = env_list_size();
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		panic("malloc");
	i = 0;
	while (env)
	{
		envp[i++] = join_env(env->key, env->value);
		env = env->next;
	}
	envp[i] = NULL;
	free_tab(g_shell->envp);
	g_shell->envp = envp;
}
