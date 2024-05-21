/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	free_env(void)
{
	t_env	*next;
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

void	cleanup_shell(void)
{
	free_env();
	free(g_shell->cwd);
	free(g_shell->home);
	g_shell->cwd = NULL;
	free_tab(g_shell->envp);
	g_shell->envp = NULL;
	g_shell->term.c_lflag |= ECHOCTL;
	free(g_shell->last_exit.str);
	if (tcsetattr(0, 0, &g_shell->term) == -1)
		perror("");
	ft_clear_history();
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	if (get_env("HOME"))
	{
		free(g_shell->home);
		g_shell->home = ft_strdup(get_env("HOME"));
	}
	g_shell->secondary_input = dup(0);
	free_tree(g_shell->tree);
	g_shell->tree = NULL;
	free(g_shell->input);
	g_shell->input = NULL;
	free(g_shell->prompt);
	g_shell->prompt = NULL;
	g_shell->has_syntax_error = false;
	g_shell->lexer_idx = 0;
	g_shell->has_heredoc = false;
}
