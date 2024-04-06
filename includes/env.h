/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:11 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/06 03:19:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

# define ENV_H

# include "libft.h"

char	**parse_env(char **envp);
char	*get_env(char *name);
size_t	ft_tabsize(char **tab);
void	set_env(char *key, char *value);

#endif