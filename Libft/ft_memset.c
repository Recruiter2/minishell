/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:11 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/11 21:20:28 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int c, size_t SIZE)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = buffer;
	while (i < SIZE)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (buffer);
}
