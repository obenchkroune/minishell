/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:54:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/08 10:54:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include <libft.h>
# include <stdbool.h>

typedef enum e_token_type
{
    T_REDIRECT_OUT,
    T_REDIRECT_OUT_APPEND,
    T_REDIRECT_IN,
    T_HEREDOC,
    T_PIPE,
    T_ENV_VAR,
	T_WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *token);
t_token	*tokenize(const char *input);
void	free_tokens(t_token *token);
bool	has_valid_syntax(t_token *token);

#endif