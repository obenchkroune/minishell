/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/21 22:37:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <libft.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"

void	panic(const char *msg);
int		ft_isspace(int c);

#endif
