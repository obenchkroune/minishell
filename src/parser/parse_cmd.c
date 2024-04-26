/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:29:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 14:12:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

t_redir_type	get_redir_type(t_token token)
{
	t_token_type	type;

	type = token.type;
	if (type == T_APPEND)
		return (REDIR_APPEND);
	else if (type == T_REDIR_IN)
		return (REDIR_IN);
	else if (type == T_REDIR_OUT)
		return (REDIR_OUT);
	else
	{
		g_shell->has_heredoc = true;
		return (REDIR_HEREDOC);
	}
}

static bool	is_regular_file(const char *file)
{
	int			fd;
	struct stat	file_info;

	fd = open(file, O_RDONLY);
	if (fstat(fd, &file_info) < 0)
		panic("fstat");
	return (close(fd), !S_ISDIR(file_info.st_mode));
}

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	i = 0;
	result = NULL;
	cmd = ft_expand(cmd);
	if (!is_regular_file(cmd) || !get_env("PATH"))
		return (free(cmd), NULL);
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	path = ft_split(get_env("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		result = ft_strjoin(path[i], slash_cmd);
		if (access(result, X_OK | F_OK) == 0)
			break ;
		free(result);
		result = NULL;
		i++;
	}
	return (free(slash_cmd), free_tab(path), free(cmd), result);
}

t_node	*parse_cmd(void)
{
	t_node		*node;
	t_list		*args;
	t_redir		*redir;

	if (peek() == T_PIPE || peek() == T_ERROR)
	{
		syntax_error(NULL);
		return (NULL);
	}
	if (peek() == T_EOF)
		return (NULL);
	args = NULL;
	redir = NULL;
	node = create_node(N_CMD, NULL, NULL);
	while (peek() != T_PIPE && peek() != T_EOF)
	{
		if (peek() == T_WORD)
			ft_lstadd_back(&args, ft_lstnew(get_next_token().value));
		else
			ft_append_redir(&redir);
	}
	node->redir = redir;
	if (args)
		node->cmd = create_cmd(get_executable(args->content), ft_lsttab(args));
	return (free_list(args), node);
}
