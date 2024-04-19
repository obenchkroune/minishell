/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:33:13 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 16:44:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"
# include <stdbool.h>
# define NO_OLDPWD "cd: OLDPWD environment variable has not been set."
# define NO_HOME "cd: HOME environment variable has not been set."

void	ft_echo(t_cmd *cmd);
void	ft_cd(t_cmd *cmd);
void	ft_pwd(void);
void	ft_env(void);
void	ft_export(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
bool	ft_is_builtin(t_cmd *cmd);
void	ft_history(t_cmd *cmd);
#endif