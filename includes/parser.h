/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 01:50:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdlib.h>
# include "lexer.h"


typedef enum e_redir_type
{
    IO_IN,
    IO_OUT,
    IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_node_type
{
	N_PIPE,
	N_CMD,
	N_AND,
	N_OR
}	t_node_type;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

typedef struct s_io
{
	t_token_type	type;
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_node	*parse_input(char *input);
t_cmd	*parse_cmd(t_token *token);
t_node	*create_pipe(t_node *left, t_node *right);
t_node	*parse_pipe(t_lexer *lexer);
t_io	*parse_io(t_lexer *l);

t_io	*create_io(char *file, int fd, t_token_type type);
t_cmd	*create_cmd(char *path, char **argv);
t_node	*create_node(t_node_type type, t_cmd *cmd, t_io *io);

#endif
