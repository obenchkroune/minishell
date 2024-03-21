/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/20 01:16:20 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdlib.h>
#include "lexer.h"

typedef enum e_redir_type
{
    IO_IN,
    IO_OUT,
    IO_HEREDOC,
	IO_APPEND
}	t_redir_type;

typedef enum e_node_type
{
	N_PIPE,
	N_REDIR,
	N_CMD,
	N_AND,
	N_OR
}	t_node_type;

typedef struct s_node
{
	t_node_type	type;
}	t_node;

typedef struct s_cmd
{
	t_node_type	type;
	char		*path;
	char		**argv;
}	t_cmd;

typedef struct s_meta
{
	t_node_type	type;
	t_node		*right;
	t_node		*left;
}	t_meta;

typedef struct s_redir
{
	t_node_type		type;
	t_token_type	token_type;
	char			*file;
	int				fd;
	t_node			*next;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

void	panic(const char *msg);
t_node	*create_meta(t_node_type type, t_node *left, t_node *right);
t_node	*create_command(char *path, char **argv);
t_node	*create_redir(t_node *cmd, t_token *token);
t_node	*parse(t_token *token);
t_node	*parse_command(t_token **token);
t_node	*parse_pipe(t_token **token);
t_node	*parse_redir(t_node *node, t_token **token);
int		is_redir_token(t_token_type type);

#endif
