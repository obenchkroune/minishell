/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:00:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/05 05:44:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env(char *key)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		panic("malloc");
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	free_tab(g_shell->envp);
	g_shell->envp = env_tab(g_shell->env);
	return (env);
}

t_env	*set_env(char *key, char *value)
{
	t_env	*env;

	env = get_env(key);
	if (!env)
	{
		env = create_env(key, value);
		env->next = g_shell->env;
		g_shell->env = env;
		return (env);
	}
	free(env->value);
	env->value = ft_strdup(value);
	free_tab(g_shell->envp);
	g_shell->envp = env_tab(g_shell->env);
	return (env);
}

char	*combine_env(t_env *env)
{
	size_t	len;
	char	*result;

	if (!env || !env->key)
		return (NULL);
	len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
	result = ft_calloc(len, sizeof(char));
	if (!result)
		panic("malloc");
	ft_strlcat(result, env->key, len);
	ft_strlcat(result, "=", len);
	if (env->value != NULL)
		ft_strlcat(result, env->value, len);
	return (result);
}

size_t	ft_envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_tab(t_env *env)
{
	size_t	len;
	char	**env_tab;
	size_t	i;

	len = ft_envsize(env);
	env_tab = ft_calloc(len + 1, sizeof(char **));
	if (!env_tab)
		panic("malloc");
	i = 0;
	while (env)
	{
		env_tab[i++] = combine_env(env);
		env = env->next;
	}
	return (env_tab);
}
