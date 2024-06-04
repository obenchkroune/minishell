/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:11 by yaharkat          #+#    #+#             */
/*   Updated: 2024/06/04 18:11:15 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_constructor(const char *key, const char *value);
void	update_envp(void);
t_env	*parse_env(char **envp);
char	*get_env(const char *name);
size_t	ft_tabsize(char **tab);
void	set_env(const char *key, const char *value);
void	delete_env(char *key);
void	add_env(t_env **root, char *key, char *value);
size_t	env_list_size(void);
char	*join_env(char *name, char *value);
void	append_env(char *key, char *value);
void	update_envp(void);

#endif
