/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 17:39:30 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define COLOR_BOLD "\e[1m"
# define COLOR_OFF "\e[m"

# define RED "\001\x1b[31m\002"
# define GREEN "\001\x1b[32m\002"
# define YELLOW "\001\x1b[33m\002"
# define BLUE "\001\x1b[34m\002"
# define MAGENTA "\001\x1b[35m\002"
# define CYAN "\001\x1b[36m\002"
# define RESET "\001\x1b[0m\002"

# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "history.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "signals.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <dirent.h>

typedef struct s_last_exit
{
	int		status;
	char	*str;
}	t_last_exit;

typedef struct s_shell
{
	t_node			*tree;
	char			*input;
	size_t			lexer_idx;
	t_history		*history;
	char			*cwd;
	t_env			*env;
	char			**envp;
	t_last_exit		last_exit;
	char			*prompt;
	bool			has_syntax_error;
	bool			has_heredoc;
	char			term_buffer[2048];
	struct termios	term;
	int				secondary_input;
}					t_shell;

extern t_shell		*g_shell;

void				set_status(int status);
char				*ft_strreplace(char *str, char *find, char *replace);
void				display_prompt(void);
void				panic(char *msg);
void				panic_minishell(char *msg, int status);
void				syntax_error(char *s);
int					ft_isspace(int c);
bool				is_empty(char *str);
void				init_shell(char **envp);
void				cleanup_shell(void);
void				free_tab(char **tab);
void				cleanup_rotation(void);
char				*ft_strreplace(char *str, char *find, char *replace);
int					set_terminal_attributes(void);
char				*get_display_line(void);
void				cd_error(char *path);
void				cd_relative(char *path);
void				cd_absolute(char *path);
void				set_pwd(char *path);

#endif
