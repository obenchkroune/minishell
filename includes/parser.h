/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/17 09:47:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdlib.h>
#include "lexer.h"

typedef enum e_node_type
{
	N_PIPE,
	N_REDIR,
	N_EXEC,
	N_LIST,
}	t_node_type;

typedef struct s_node
{
	t_node_type	type;
}	t_node;

typedef struct s_exec
{
	t_node_type	type;
	char		*path;
	char		**argv;
}	t_exec;

typedef struct s_pipe
{
	t_node_type	type;
	t_node		*right;
	t_node		*left;
}	t_pipe;

typedef struct s_redir
{
	t_node_type	type;
	char		*file;
	t_node		*cmd;
}	t_redir;

void	panic(const char *msg);
t_node	*create_pipe(t_node *left, t_node *right);
t_node	*create_exec(char *path, char **argv);
t_node	*create_redir(t_node *cmd, char *file);
t_node	*parse_tree(t_tok **tokens);


#endif
