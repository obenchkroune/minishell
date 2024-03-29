/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 22:48:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdlib.h>
# include "lexer.h"
# include "env.h"


typedef enum e_redir_type
{
    IO_IN,
    IO_OUT,
    IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_node_type
{
	N_PIPE = 0,
	N_CMD,
	N_REDIR
}	t_node_type;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

typedef struct s_io
{
	t_tok_kind	type;
	char			*file;
	int				fd;
	struct s_io		*prev;
	struct s_io		*next;
}	t_io;

typedef struct s_node
{
	t_node_type		type;
	t_cmd			*cmd;
	t_io			*io;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*create_node(t_node_type type, t_node *left, t_node *right);
t_node	*create_cmd_node(t_cmd *cmd);
t_env	*parse_env(char **envp);
t_node	*parse_input(char *input);
char	*get_executable(char *cmd);
size_t	get_argc(t_token *token);
char	**parse_argv(t_token **token);
void	free_tree(t_node *node);

#endif
