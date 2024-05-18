/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:14 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/18 14:06:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include <stdbool.h>
# include <stdlib.h>

typedef enum e_token_type
{
	T_EOF = 0,
	T_APPEND,
	T_REDIR_IN,
	T_PIPE,
	T_REDIR_OUT,
	T_HEREDOC,
	T_WORD,
	T_SEMICOL,
	T_OPEN_PAREN,
	T_CLOSE_PAREN,
	T_AND,
	T_OR,
	T_ERROR
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

t_token				get_next_token(void);
t_token_type		peek(void);
void				skip_whitespace(void);

#endif
