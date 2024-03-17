/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:54:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/17 09:05:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# define MAX_ARGS 10
# define WHITESPACE " \t\v\r\n"
# define SYMBOLS "()|<>;&"

# include <libft.h>
# include <stdbool.h>

typedef enum e_tok_type
{
	T_EOL,
	T_WORD,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_OPEN_PAREN,
	T_CLOSE_PAREN,
	T_AND,
	T_OR,
	T_SEMICOL,
	T_PIPE,
}	t_tok_type;

typedef struct s_tok
{
	enum e_tok_type	type;
	char			*value;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

void	panic(const char *msg);
t_tok	*get_next_token(char *input);
void	append_token(t_tok **head, t_tok *node);
t_tok	*create_token(char *value, t_tok_type type);
t_tok	*tokenize(char *input);
void	free_tokens(t_tok *tok);

#endif
