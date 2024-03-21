/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:54:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/19 05:28:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# define WHITESPACE " \t\v\r\n"
# define SYMBOLS "()|<>;&"

# include <libft.h>
# include <stdbool.h>

typedef enum e_token_type
{
	T_COMMAND,
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
}	t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

void	skip_whitespace(char **str);
void	panic(const char *msg);
t_token	*tokenize(char *input);

#endif
