/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/28 02:34:20 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_kind	peek_kind(t_lexer *lexer)
{
	char	*curr;

	curr = &lexer->val[lexer->i];
	if (*curr == '\0')
		return (T_EOL);
	else if (ft_strncmp(">>", curr, 2) == 0)
		return (T_DGREAT);
	else if (ft_strncmp("<<", curr, 2) == 0)
		return (T_DLESS);
	else if (*curr == '>')
		return (T_GREAT);
	else if (*curr == '<')
		return (T_LESS);
	else if (*curr == '|')
		return (T_PIPE);
	else
		return (T_WORD);
}

char	*get_next_word(t_lexer *lexer)
{
	size_t	start;

	start = lexer->i;
	if (ft_strchr("'\"", lexer->val[lexer->i]))
		return (get_quoted_word(lexer));
	while (is_word_char(lexer->val[lexer->i]))
		lexer->i++;
	return (ft_substr(lexer->val, start, lexer->i - start));
}

void	advance_index(t_lexer *lexer, t_token *token)
{
	if (token->kind == T_EOL)
		return ;
	if (token->kind == T_WORD)
		token->value = get_next_word(lexer);
	else if (token->kind == T_DGREAT || token->kind == T_DLESS)
		lexer->i += 2;
	else
		lexer->i += 1;
}

t_token	*get_next_token(t_lexer *lexer)
{
	t_token	*token;

	if (lexer->val[lexer->i] == '\0')
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		panic("malloc");
	while (ft_isspace(lexer->val[lexer->i]) && lexer->val[lexer->i] != '\0')
		lexer->i++;
	token->kind = peek_kind(lexer);
	token->value = NULL;
	advance_index(lexer, token);
	return (token);
}

t_token	*tokenize(char *input)
{
	t_token	*token;
	t_token	*head;
	t_lexer	lexer;

	lexer.i = 0;
	lexer.val = input;
	token = get_next_token(&lexer);
	head = token;
	while (peek_kind(&lexer) != T_EOL)
	{
		token->next = get_next_token(&lexer);
		token->next->prev = token;
		token = token->next;
	}
	token->next = NULL;
	return (head);
}
