/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/15 07:58:55 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdlib.h>
# include "lexer.h"

typedef enum e_node_type
{
	N_PIPE,
	N_REDIR,
	N_EXEC,
	N_LIST,
}	t_node_type;

typedef struct s_node
{
	enum e_node_type	type;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_node;

#endif
