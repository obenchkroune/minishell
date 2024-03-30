/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:11 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:28:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*get_env(char *key);
char				**env_tab(t_env *env);
t_env				*set_env(char *key, char *value);
char				**env_tab(t_env *env);
void				free_env(t_env *env);
t_env				*create_env(char *key, char *value);

#endif