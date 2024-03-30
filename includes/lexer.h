/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:14 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:28:15 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_lexer
{
	char			*val;
	size_t			i;
}					t_lexer;

typedef enum e_tok_kind
{
	T_EOL = 0,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_LESS,
	T_GREAT,
	T_WORD,
}					t_tok_kind;

typedef struct s_token
{
	t_tok_kind		kind;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

bool				is_meta_char(char c);
bool				is_word_char(char c);
char				*get_quoted_word(t_lexer *lexer);
t_token				*get_next_token(t_lexer *lexer);
void				advance_index(t_lexer *lexer, t_token *token);
t_token				*tokenize(char *input);
void				free_tokens(t_token *token);

#endif