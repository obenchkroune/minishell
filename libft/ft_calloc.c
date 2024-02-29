/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:32:29 by yaharkat          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:42 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	buffer = malloc(nmemb * size);
	if (buffer)
		ft_bzero(buffer, nmemb * size);
	return (buffer);
}
