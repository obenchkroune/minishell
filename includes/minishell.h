/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/05 05:41:25 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_shell
{
	t_env		*env;
	t_node		*tree;
	char		*input;
	char		*cwd;
	int			last_exit_status;
}				t_shell;

extern t_shell	*g_shell;

void			panic(char *msg);
void			panic_minishell(char *msg, int status);
void			syntax_error(char *msg, char *cmd, ssize_t pos);
int				ft_isspace(int c);
bool			is_empty(char *str);
void			handle_sigint(int signal);
void			init_shell(char **envp);
void			cleanup_shell(void);
void			free_tab(char **tab);
void			cleanup_rotation(void);
char			*ft_strreplace(char *str, char *find, char *replace);

#endif
