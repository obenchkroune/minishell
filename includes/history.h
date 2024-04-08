/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 02:42:56 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/08 02:54:29 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_history
{
	char				*value;
	struct s_history	*next;
}						t_history;

void					set_history(char *line);
void					ft_clear_history(void);
#endif