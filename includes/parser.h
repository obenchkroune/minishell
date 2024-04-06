/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 04:49:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "env.h"
# include "lexer.h"
# include <libft.h>
# include <stdlib.h>

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}					t_redir_type;

typedef enum e_node_type
{
	N_PIPE = 0,
	N_CMD,
	N_REDIR
}					t_node_type;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
}					t_cmd;

typedef struct s_redir
{
	t_redir_type		type;
	char			*file;
	int				fd;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

typedef struct s_node
{
	t_node_type		type;
	t_cmd			*cmd;
	t_redir			*redir;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

t_node				*parse_input(void);
t_node				*create_node(t_node_type type, t_node *left, t_node *right);
t_redir				*create_redir(t_redir_type type, char *file);
t_cmd				*create_cmd(char *path, char **argv);
char				**ft_lsttab(t_list *list);
int					ft_append_redir(t_redir **root, t_token prev_token);
t_redir_type		get_redir_type(t_token token);
void				free_tree(t_node *node);



#endif
