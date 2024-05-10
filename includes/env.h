/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:11 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/10 11:42:05 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

# include "libft.h"

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

t_env   *env_constructor(char *key, char *value);
void	update_envp(void);
t_env	*parse_env(char **envp);
char	*get_env(char *name);
size_t	ft_tabsize(char **tab);
void	set_env(char *key, char *value);
void    delete_env(char *key);
void	add_env(t_env **root, char *key, char *value);
t_env	*env_constructor(char *key, char *value);
size_t	env_list_size(void);
char	*join_env(char *name, char *value);
void	update_envp(void);

#endif