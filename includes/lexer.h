#ifndef LEXER_H

# define LEXER_H

#include <stddef.h>

typedef struct s_lexer
{
	size_t	cur;
	char	*input;
}	t_lexer;

typedef enum e_token_type
{
	T_CMD,
	T_OUT,
	T_IN,
	T_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_AND,
	T_OR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token			*get_next_token(t_lexer *l);
t_token_type	peek(t_lexer *lexer);

#endif