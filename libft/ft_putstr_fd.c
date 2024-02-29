/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:00:21 by yaharkat          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:42 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (ft_putstr_fd("(null)", 1));
	return (write(fd, s, ft_strlen(s)));
}
