/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_unclosed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:44 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/13 15:54:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    read_unclosed_pipe(t_token_type token)
{
    char    *line;
    char    *temp;

    while (peek() == token && !g_shell->has_syntax_error
        && g_shell->secondary_input != -1)
    {
        write(1, "> ", 2);
        line = get_next_line(g_shell->secondary_input);
        if (!line)
        {
            syntax_error("syntax error: unexpedted end of file");
            break ;
        }
        line[ft_strlen(line) - 1] = '\0';
        temp = g_shell->input;
        g_shell->input = ft_strjoin(g_shell->input, line);
        free(temp);
    }
}
