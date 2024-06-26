/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:38:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"
# include "lexer.h"
# include "libft.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

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
	N_REDIR,
	N_SEMICOL,
	N_SUBSHELL,
	N_AND,
	N_OR,
}					t_node_type;

typedef struct s_cmd
{
	char			*path;
	int				argc;
	char			**argv;
}					t_cmd;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
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

typedef enum e_arg_type
{
	ARG_PLAIN,
	ARG_SINGLE_QUOTE,
	ARG_DOUBLE_QUOTE
}					t_arg_type;

typedef struct s_arg
{
	char			*content;
	t_arg_type		type;
	struct s_arg	*next;
}					t_arg;

char				**get_path(void);
char				*get_executable(char *cmd);
bool				is_redir_token(t_token_type type);
char				*get_wildcard_pattern(char *arg);
char				*add_file_to_string(char *dst, char *file);
t_list				*get_pattern_files(char *pattern);
void				expand_wildcard(char **result, char **arg);
bool				check_wildcard(char *pattern, char *string);
char				*append_input(char *s1, char *s2);
char				*join_args(t_arg *args, bool expand_special);
char				*replace_env_vars(char *arg, t_arg_type type);
t_arg				*create_arg_node(char *value, t_arg_type type);
void				cleanup_arg_nodes(t_arg *args);
void				add_arg_node(t_arg **root, t_arg *arg);
void				free_list(t_list *list);
void				free_cmd(t_cmd *cmd);
void				free_redir(t_redir *io);
void				free_matrix(char **matrix);
char				*ft_expand(const char *str, bool expand_special);
void				parse_input(void);
t_node				*create_node(t_node_type type, t_node *left, t_node *right);
t_redir				*create_redir(t_redir_type type, char *file);
t_cmd				*create_cmd(char *path, char **argv);
char				**ft_lsttab(t_list *list);
void				ft_append_redir(t_redir **root);
t_redir_type		get_redir_type(t_token token);
void				free_tree(t_node *node);
char				**expand_argv(char **argv);
t_node				*parse_cmd(void);
t_node				*parse_ast(void);
int					get_redir_fd(t_redir *redir);
t_node				*parse_meta(t_node *node);
void				expand_wildcard_args(t_list *args);

#endif
