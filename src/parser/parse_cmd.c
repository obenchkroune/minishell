/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:29:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/19 07:59:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "libft.h"

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

static bool	check_file(const char *file)
{
	int			fd;
	struct stat	file_info;

	if (access(file, F_OK | R_OK) != 0)
		return (false);
	fd = open(file, O_RDONLY);
	if (fstat(fd, &file_info) < 0)
		return (close(fd), false);
	close(fd);
	return (S_ISREG(file_info.st_mode));
}

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	if (!cmd)
		return (NULL);
	i = 0;
	result = NULL;
	cmd = ft_expand(cmd);
	if (ft_strchr(cmd, '/') != NULL && check_file(cmd))
		return (cmd);
	path = ft_split(get_env("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		result = ft_strjoin(path[i], slash_cmd);
		if (check_file(result))
			break ;
		free(result);
		result = NULL;
		i++;
	}
	(free(slash_cmd), free_tab(path), free(cmd));
	return (result);
}

void	expand_wildcard_args(t_list *args)
{
	t_list	*node;
	t_list	*files_list;
	char	*temp;

	node = args;
	while (node)
	{
		if (ft_strchr(node->content, '*')
			&& !ft_strchr(node->content, '"')
			&& !ft_strchr(node->content, '\''))
		{
			files_list = get_pattern_files(node->content);
			if (files_list)
			{
				ft_lstadd_back(&files_list, node->next);
				temp = node->content;
				node->content = files_list->content;
				node->next = files_list->next;
				free(temp), free(files_list);
			}
		}
		node = node->next;
	}
}

t_node	*parse_cmd(void)
{
	t_node	*node;
	t_list	*args;
	t_redir	*redir;

	if (peek() == T_EOF)
		return (NULL);
	if (peek() != T_WORD && !is_redir_token(peek()))
		return (syntax_error(NULL), NULL);
	args = NULL;
	redir = NULL;
	node = create_node(N_CMD, NULL, NULL);
	while (peek() == T_WORD || is_redir_token(peek()))
	{
		if (peek() == T_WORD)
			ft_lstadd_back(&args, ft_lstnew(get_next_token().value));
		else
			ft_append_redir(&redir);
	}
	node->redir = redir;
	if (args)
	{
		expand_wildcard_args(args);
		node->cmd = create_cmd(NULL, ft_lsttab(args));
	}
	return (free_list(args), node);
}
